/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "app.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define TASK_PRIO          (configMAX_PRIORITIES - 1)
#define MAXELEMENTS 5
#define MSGSIZE		11

typedef struct QUEUE {
	int elements[MAXELEMENTS];
	int head;
	int tail;
} QUEUE;

QUEUE CircularBuff;
SemaphoreHandle_t xSemaphore_console;
static uint8_t u8Message[MSGSIZE] = {"ITESO_RULES"};
static uint8_t u8NextChar = 0U;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void producer_task(void *pvParameters);
static void consumer_task(void *pvParameters);

/*******************************************************************************
 * Code
 ******************************************************************************/
static void _initqueue(QUEUE *thequeue)
{
	thequeue->head=0;
	thequeue->tail=0;
}

static void _enqueue(QUEUE *thequeue,int value)
{
	thequeue->elements[thequeue->head]=value;
	// increase the pointer
	thequeue->head++;
	thequeue->head=thequeue->head%MAXELEMENTS;
}

static int _dequeue(QUEUE *thequeue)
{
	int valueret;
	valueret=thequeue->elements[thequeue->tail];
	// increase the pointer
	thequeue->tail++;
	thequeue->tail=thequeue->tail%MAXELEMENTS;
	return(valueret);
}

static int _isqueueempty(QUEUE *thequeue)
{
	return(thequeue->head==thequeue->tail);
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Init board hardware. */
    BOARD_InitHardware();
    if (xTaskCreate(producer_task, "PRODUCER_TASK", configMINIMAL_STACK_SIZE + 128, NULL, TASK_PRIO, NULL) != pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }
    /* Start scheduling. */
    vTaskStartScheduler();
    for (;;)
        ;
}

/*!
 * @brief Task producer_task.
 */
static void producer_task(void *pvParameters)
{
    uint32_t i;
    uint8_t u8Count;
    uint8_t u8Enqueue;

    PRINTF("Producer_task created.\r\n");
    xSemaphore_console = xSemaphoreCreateCounting( MAXELEMENTS-1 , MAXELEMENTS-1 );
    if (xSemaphore_console == NULL)
    {
        PRINTF("xSemaphore_producer creation failed.\r\n");
        vTaskSuspend(NULL);
    }

    _initqueue(&CircularBuff);

    if (xTaskCreate(consumer_task, "CONSUMER_TASK", configMINIMAL_STACK_SIZE + 128, NULL, TASK_PRIO, NULL) != pdPASS)
    {
		PRINTF("Task creation failed!.\r\n");
		vTaskSuspend(NULL);
	}

    while (1)
    {
    	if(u8NextChar < MSGSIZE)
    	{
    		if (xSemaphoreTake(xSemaphore_console, portMAX_DELAY) == pdTRUE)
			{
    			_enqueue(&CircularBuff,u8Message[u8NextChar]);
    			u8NextChar++;
			}
    	}
		else
		{
			taskYIELD();
		}
    }
}

/*!
 * @brief Task consumer_task.
 */
static void consumer_task(void *pvParameters)
{
	uint8_t u8Value = 0U;

    while (1)
    {
    	if(_isqueueempty(&CircularBuff))
    	{
    		taskYIELD();
    	}
    	else
    	{
    		u8Value = _dequeue(&CircularBuff);
    		PRINTF("%c", u8Value);
    		xSemaphoreGive(xSemaphore_console);
    	}
    }
}
