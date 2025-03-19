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
#include "SchedPrio_cfg.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define TOTAL_TASKS (TotalTasks - 1)
#define HIGH_PRIO_INDEX (Task_ID_HPrio - 1)
#define MAX_NODES 	(TOTAL_TASKS)

typedef struct {
	uint8_t u8TaskID;
	PtrTask PtrFunc;
	uint8_t u8Priority;
	uint8_t u8TaskState;
}stTasksFt;

typedef struct stLinkedList{
	struct stLinkedList* pPrevNode;
	struct stLinkedList* pNextNode;
	stTasksFt* pstNodeData;
}stLinkedList;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool g_ButtonPress = false;
stTasksFt Task_Config[TOTAL_TASKS] = TaskScheduler;
stLinkedList LinkedListNodes[MAX_NODES];
stLinkedList* Task_RdyListHead;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Interrupt service fuction of switch.
 *
 * This functions change interrupt flags state
 */
void BOARD_SW_IRQ_HANDLER(void)
{
    GPIO_GpioClearInterruptFlags(BOARD_SW_GPIO, 1U << BOARD_SW_GPIO_PIN);
    /* Change state of button. */
    g_ButtonPress = true;
    SDK_ISR_EXIT_BARRIER;
}


/*This function changes the status of a task from 'suspended' to 'ready'*/
static void vChangeStatus(void)
{
	for(uint8_t u8Index = 0U; u8Index < (uint8_t)TOTAL_TASKS - 1; u8Index++)
	{
		if(Task_Config[u8Index].u8TaskState == (uint8_t)Task_Suspended)
		{
			Task_Config[u8Index].u8TaskState = (uint8_t)Task_Ready;
		}
	}

	if(g_ButtonPress == true)
	{
		Task_Config[HIGH_PRIO_INDEX].u8TaskState = (uint8_t)Task_Ready;
		g_ButtonPress = false;
	}
}

static void vAddNewNode(uint8_t u8IndexData)
{
	stLinkedList* pstNode = (stLinkedList*)Task_RdyListHead;
	uint8_t u8NewNode = 0xFF;

	for(uint8_t u8Index = 0U; u8Index < MAX_NODES; u8Index++)
	{
		if(LinkedListNodes[u8Index].pstNodeData == (stTasksFt*)NULL)
		{
			u8NewNode = u8Index;
			break;
		}
	}

	if(u8NewNode != (uint8_t)0xFF)
	{
		if(pstNode != (stLinkedList*)NULL)
		{
			while(pstNode->pNextNode != (stLinkedList*)NULL)
			{
				pstNode = pstNode->pNextNode;
			}

			pstNode->pNextNode = (stLinkedList*)&LinkedListNodes[u8NewNode];
			pstNode->pNextNode->pPrevNode = pstNode;
			pstNode->pNextNode->pstNodeData = (stTasksFt*)&Task_Config[u8IndexData];
		}
		else
		{
			Task_RdyListHead = (stLinkedList*)&LinkedListNodes[u8NewNode];
			Task_RdyListHead->pstNodeData = (stTasksFt*)&Task_Config[u8IndexData];
		}
	}
}

static stLinkedList* pstSearchNode(uint8_t u8IndexData)
{
	stLinkedList* pstNode = (stLinkedList*)NULL;
	stLinkedList* pstNodeFound = (stLinkedList*)NULL;

	pstNode = Task_RdyListHead;

	while(pstNode != (stLinkedList*)NULL)
	{
		if(Task_Config[u8IndexData].u8TaskID == pstNode->pstNodeData->u8TaskID)
		{
			pstNodeFound = pstNode;
			break;
		}

		pstNode = pstNode->pNextNode;
	}

	return pstNodeFound;
}

/*This function adds all tasks with a 'ready' status to the queue*/
static void vAddTasks2Buff(void)
{
	stLinkedList* pstNodeFound = (stLinkedList*)NULL;

	for(uint8_t u8Index = 0U; u8Index < (uint8_t)TOTAL_TASKS; u8Index++)
	{

		if(Task_Config[u8Index].u8TaskState == (uint8_t)Task_Ready)
		{
			pstNodeFound = pstSearchNode(u8Index);

			if(pstNodeFound == (stLinkedList*)NULL)
			{
				vAddNewNode(u8Index);
			}
		}
	}
}

static void vSwapNodes(stLinkedList* pstNode)
{
	stLinkedList pstNodeAux;

	pstNodeAux.pNextNode = pstNode->pNextNode;
	pstNodeAux.pPrevNode = pstNode->pPrevNode;

	pstNode->pPrevNode = pstNode->pNextNode;
	pstNode->pNextNode = pstNode->pNextNode->pNextNode;

	if(pstNodeAux.pPrevNode != (stLinkedList*)NULL)
	{
		pstNodeAux.pPrevNode->pNextNode = pstNodeAux.pNextNode;
	}

	if(pstNodeAux.pNextNode->pNextNode != (stLinkedList*)NULL)
	{
		pstNodeAux.pNextNode->pNextNode->pPrevNode = pstNodeAux.pNextNode->pPrevNode;
	}

	pstNodeAux.pNextNode->pNextNode = pstNode;
	pstNodeAux.pNextNode->pPrevNode = pstNodeAux.pPrevNode;
}

static void vRearrangeTasks(void)
{
	stLinkedList* pstNode = (stLinkedList*)NULL;
	uint8_t u8Flag = 0U;

	do
	{
		u8Flag = 0U;
		pstNode = Task_RdyListHead;

		while(pstNode->pNextNode != (stLinkedList*)NULL)
		{
			if(pstNode->pstNodeData->u8Priority > pstNode->pNextNode->pstNodeData->u8Priority)
			{
				if(pstNode == Task_RdyListHead)
				{
					Task_RdyListHead = pstNode->pNextNode;
				}

				vSwapNodes(pstNode);
				u8Flag = 1U;
			}
			else
			{
				pstNode = pstNode->pNextNode;
			}
		}
	}while(u8Flag);
}

/*This function executes the tasks */
static void vExecuteTasks(void)
{
	stLinkedList* pstNode = (stLinkedList*)Task_RdyListHead;
	uint8_t u8TaskId_Index = TOTAL_TASKS;
	uint8_t u8TaskId = 0U;

	if(pstNode != (stLinkedList*)NULL)
	{
		u8TaskId = pstNode->pstNodeData->u8TaskID;
	}

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
		pstNode->pstNodeData->PtrFunc(u8TaskId);
		Task_Config[u8TaskId_Index].u8TaskState = (uint8_t)Task_Suspended;
	}
}

/*This function deletes executed tasks from the queue */
static void vDequeue(void)
{
	stLinkedList* pstNode = (stLinkedList*)Task_RdyListHead;
	stLinkedList* pstNodeAux = (stLinkedList*)NULL;
	uint8_t u8TaskId_Index = TOTAL_TASKS;
	uint8_t u8TaskId = 0U;

	if(pstNode != (stLinkedList*)NULL)
	{
		u8TaskId = pstNode->pstNodeData->u8TaskID;
	}

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
		pstNodeAux = pstNode;
		Task_RdyListHead = pstNode->pNextNode;
		pstNode->pstNodeData = (stTasksFt*)NULL;
		pstNode->pNextNode->pPrevNode = (stLinkedList*)NULL;
		pstNode->pNextNode = (stLinkedList*)NULL;
		pstNode->pPrevNode = (stLinkedList*)NULL;
	}
}

/*This function evaluates values set on TaskScheduler*/
static void vCheckConfig(void)
{
	uint8_t u8Index = (uint8_t)0U;

	for(u8Index = 0U; u8Index < (uint8_t)TOTAL_TASKS; u8Index++)
	{
		assert(Task_Config[u8Index].PtrFunc != (PtrTask)NULL);
		assert(Task_Config[u8Index].u8Priority > 0U);
		assert(Task_Config[u8Index].u8TaskID < (uint8_t)TotalTasks);
		assert(Task_Config[u8Index].u8TaskState < (uint8_t)Total_States);
	}
}

void Task_execute(uint8_t u8TaskId)
{
	PRINTF("Task %d running\r\n", u8TaskId);
 	SDK_DelayAtLeastUs(1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
}

void Task_execute_HighPrio(uint8_t u8TaskId)
{
	PRINTF("Task %d running\r\n", u8TaskId);
	SDK_DelayAtLeastUs(1000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
	GPIO_PortToggle(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
}

void vInit(void)
{
    /* Define the init structure for the input switch pin */
    gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput,
        0,
    };

    /* Define the init structure for the output LED pin */
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        0,
    };

    BOARD_InitHardware();

    /* Print a note to terminal. */
    PRINTF("\r\n Scheduler PRIORITY\r\n");

    GPIO_SetPinInterruptConfig(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, kGPIO_InterruptFallingEdge);

    EnableIRQ(BOARD_SW_IRQ);

    GPIO_PinInit(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, &sw_config);
    GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);

    Task_RdyListHead = (stLinkedList*)NULL;

	for(uint8_t u8Index = 0U; u8Index < MAX_NODES; u8Index++)
	{
		LinkedListNodes[u8Index].pstNodeData = (stTasksFt*)NULL;
		LinkedListNodes[u8Index].pPrevNode = (stLinkedList*)NULL;
		LinkedListNodes[u8Index].pNextNode = (stLinkedList*)NULL;
	}
}


/*!
 * @brief Main function
 */
int main(void)
{
	/*Check elements set in TaskScheduler*/
	vCheckConfig();

	/*Init drivers*/
	vInit();

    while (1)
    {
    	vChangeStatus();

    	vAddTasks2Buff();

    	vRearrangeTasks();

		vExecuteTasks();

		vDequeue();
    }
}
