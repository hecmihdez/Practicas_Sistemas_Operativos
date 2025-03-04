/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#if defined(FSL_FEATURE_SOC_PORT_COUNT) && (FSL_FEATURE_SOC_PORT_COUNT)
#include "fsl_port.h"
#endif
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "app.h"
#include "pin_mux.h"
#include "board.h"
#include "SchedFIFO_cfg.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define TOTAL_TASKS (TotalTasks - 1)
#define FIRST_INPUT (0)
#define LAST_INPUT	(TOTAL_TASKS - 1)

typedef struct {
	uint8_t u8TaskID;
	PtrTask PtrFunc;
	uint8_t u8BurstTime;
	uint8_t u8TaskState;
}stTasksFt;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
stTasksFt Task_Config[TOTAL_TASKS] = TaskScheduler;
stTasksFt Task_RdyBuff[TOTAL_TASKS] = {0};
uint8_t u8TaskInBuff = 0U;

/*******************************************************************************
 * Code
 ******************************************************************************/
static void vChangeStatus(uint8_t u8TaskId)
{
	for(uint8_t u8Index = 0U; u8Index < (uint8_t)TOTAL_TASKS; u8Index++)
	{
		if(Task_Config[u8Index].u8TaskID == u8TaskId)
		{
			Task_Config[u8Index].u8TaskState = (uint8_t)Task_Ready;
			break;
		}
	}
}

static void vAddTasks2Buff(void)
{
	uint8_t u8InBuffFlag = 0U;

	for(uint8_t u8Index = 0U; (u8Index < (uint8_t)TOTAL_TASKS)&&(u8TaskInBuff < TOTAL_TASKS); u8Index++)
	{
		u8InBuffFlag = 0U;

		if(Task_Config[u8Index].u8TaskState == (uint8_t)Task_Ready)
		{
			for(uint8_t u8IndexBuff = 0U; u8IndexBuff < (uint8_t)TOTAL_TASKS; u8IndexBuff++)
			{
				if(Task_Config[u8Index].u8TaskID == Task_RdyBuff[u8IndexBuff].u8TaskID)
				{
					u8InBuffFlag = 1U;
					break;
				}
			}

			if(u8InBuffFlag == 0U)
			{
				Task_RdyBuff[u8TaskInBuff].PtrFunc = Task_Config[u8Index].PtrFunc;
				Task_RdyBuff[u8TaskInBuff].u8BurstTime = Task_Config[u8Index].u8BurstTime;
				Task_RdyBuff[u8TaskInBuff].u8TaskID = Task_Config[u8Index].u8TaskID;
				Task_RdyBuff[u8TaskInBuff].u8TaskState = Task_Config[u8Index].u8TaskState;

				u8TaskInBuff++;
			}
		}
	}
}

static void vExecuteTasks(void)
{
	uint8_t u8TaskId_Index = TOTAL_TASKS;
	uint8_t u8TaskId = Task_RdyBuff[FIRST_INPUT].u8TaskID;
	uint8_t u8TaskBurst = Task_RdyBuff[FIRST_INPUT].u8BurstTime;

	for(uint8_t u8Index = 0U; u8Index < (uint8_t)TOTAL_TASKS; u8Index++)
	{
		if(Task_Config[u8Index].u8TaskID == u8TaskId)
		{
			u8TaskId_Index = u8Index;
			break;
		}
	}

	if(u8TaskId_Index < (uint8_t)TOTAL_TASKS)
	{
		Task_Config[u8TaskId_Index].u8TaskState = (uint8_t)Task_Running;
		Task_RdyBuff[FIRST_INPUT].PtrFunc(u8TaskBurst, u8TaskId);
		Task_Config[u8TaskId_Index].u8TaskState = (uint8_t)Task_Suspended;
	}
}

static void vDequeue(void)
{
	uint8_t u8TaskId_Index = TOTAL_TASKS;
	uint8_t u8TaskId = Task_RdyBuff[FIRST_INPUT].u8TaskID;
	uint8_t u8TaskBurst = Task_RdyBuff[FIRST_INPUT].u8BurstTime;

	for(uint8_t u8Index = 0U; u8Index < (uint8_t)TOTAL_TASKS; u8Index++)
	{
		if(Task_Config[u8Index].u8TaskID == u8TaskId)
		{
			u8TaskId_Index = u8Index;
			break;
		}
	}

	if(Task_Config[u8TaskId_Index].u8TaskState == (uint8_t)Task_Suspended)
	{
		for(uint8_t u8TaskIndex = 0U; u8TaskIndex < (uint8_t)(TOTAL_TASKS - 1); u8TaskIndex++)
		{
			Task_RdyBuff[u8TaskIndex].PtrFunc = Task_RdyBuff[u8TaskIndex + 1].PtrFunc;
			Task_RdyBuff[u8TaskIndex].u8BurstTime = Task_RdyBuff[u8TaskIndex + 1].u8BurstTime;
			Task_RdyBuff[u8TaskIndex].u8TaskID = Task_RdyBuff[u8TaskIndex + 1].u8TaskID;
			Task_RdyBuff[u8TaskIndex].u8TaskState = Task_RdyBuff[u8TaskIndex + 1].u8TaskState;
		}

		Task_RdyBuff[LAST_INPUT].PtrFunc = (PtrTask)NULL;
		Task_RdyBuff[LAST_INPUT].u8BurstTime = 0U;
		Task_RdyBuff[LAST_INPUT].u8TaskID = 0U;
		Task_RdyBuff[LAST_INPUT].u8TaskState = 0U;

		u8TaskInBuff--;
	}
}

/*This function evaluates values set on StatesDefinition*/
static void vCheckConfig(void)
{
	uint8_t u8Index = (uint8_t)0U;

	for(u8Index = 0U; u8Index < (uint8_t)TOTAL_TASKS; u8Index++)
	{
		assert(Task_Config[u8Index].PtrFunc != (PtrTask)NULL);
		assert(Task_Config[u8Index].u8BurstTime < (uint8_t)Total_Burst);
		assert(Task_Config[u8Index].u8TaskID < (uint8_t)TotalTasks);
		assert(Task_Config[u8Index].u8TaskState < (uint8_t)Total_States);
	}
}

void Task_execute(uint8_t u8BurstTime, uint8_t u8TaskId)
{
	PRINTF("Task %d running\r\n", u8TaskId);
	PRINTF("Waiting %d ms\r\n", u8BurstTime);

	SDK_DelayAtLeastUs((u8BurstTime * 1000), SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}

void vInit(void)
{
    BOARD_InitHardware();

    /* Print a note to terminal. */
    PRINTF("\r\n Scheduler FIFO\r\n");
}


/*!
 * @brief Main function
 */
int main(void)
{
	/*Check elements set in StatesDefinition*/
	vCheckConfig();

	/*Init drivers*/
	vInit();

    while (1)
    {
    	for(uint8_t u8TaskIndex = 0U; u8TaskIndex < (uint8_t)TOTAL_TASKS; u8TaskIndex++)
    	{
    		if(Task_Config[u8TaskIndex].u8TaskState == (uint8_t)Task_Suspended)
    		{
    			vChangeStatus(Task_Config[u8TaskIndex].u8TaskID);
    		}
    	}

    	vAddTasks2Buff();

    	if((Task_RdyBuff[FIRST_INPUT].u8TaskState == (uint8_t)Task_Ready)&&(Task_RdyBuff[FIRST_INPUT].PtrFunc != (PtrTask)NULL))
    	{
    		vExecuteTasks();

    		vDequeue();
    	}
    }
}
