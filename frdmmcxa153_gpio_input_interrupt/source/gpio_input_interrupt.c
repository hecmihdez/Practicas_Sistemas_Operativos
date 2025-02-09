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
#include "StateMachine_cfg.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef enum {
    Cond1 = 0,
    Cond2,
    CondIndetermined
}enConditions;

typedef struct {
	StateDef PtrFunc;
	uint8_t u8StateCond1;
	uint8_t	u8StateCond2;
}stStatesCfg;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
stStatesCfg g_StatesPtrs[TotalStates] = FunctPtr;
uint8_t g_CurrentState = (uint8_t)State0;
uint8_t g_PrevState = (uint8_t)State7;

/* Whether the SW button is pressed */
volatile bool g_ButtonPress = false;
volatile bool g_Button2Press = false;


/*******************************************************************************
 * Code
 ******************************************************************************/

static uint8_t u8DetermineCond(void)
{
	uint8_t u8CondDetected = (uint8_t)CondIndetermined;
	if((g_ButtonPress)&&!(g_Button2Press))
	{
		u8CondDetected = (uint8_t)Cond1;
	}
	else if(!(g_ButtonPress)&&(g_Button2Press))
	{
		u8CondDetected = (uint8_t)Cond2;
	}
	else
	{
		/*Nothing to do*/
	}

	return u8CondDetected;
}

/*!
 * @brief Interrupt service fuction of switch.
 *
 * This function toggles the LED
 */
void BOARD_SW_IRQ_HANDLER(void)
{
    GPIO_GpioClearInterruptFlags(BOARD_SW_GPIO, 1U << BOARD_SW_GPIO_PIN);
    /* Change state of button. */
    g_ButtonPress = true;
    SDK_ISR_EXIT_BARRIER;
}

void BOARD_SW3_IRQ_HANDLER(void)
{
    /* Clear external interrupt flag. */
    GPIO_GpioClearInterruptFlags(BOARD_SW3_GPIO, 1U << BOARD_SW3_GPIO_PIN);

    /* Change state of button. */
    g_Button2Press = true;
    SDK_ISR_EXIT_BARRIER;
}

void StateMachine0(void)
{
	PRINTF(" %d state \r\n", g_CurrentState);
	/* Toggle LED. */
	GPIO_PortClear(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN);
	GPIO_PortClear(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN);
	GPIO_PortClear(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN);
}

void StateMachine1(void)
{
	PRINTF(" %d state \r\n", g_CurrentState);
	/* Toggle LED. */
	GPIO_PortClear(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN);
	GPIO_PortClear(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN);
	GPIO_PortSet(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN);
}

void StateMachine2(void)
{
	PRINTF(" %d state \r\n", g_CurrentState);
	/* Toggle LED. */
	GPIO_PortClear(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN);
	GPIO_PortSet(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN);
	GPIO_PortClear(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN);
}

void StateMachine3(void)
{
	PRINTF(" %d state \r\n", g_CurrentState);
	/* Toggle LED. */
	GPIO_PortClear(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN);
	GPIO_PortSet(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN);
	GPIO_PortSet(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN);
}

void StateMachine4(void)
{
	PRINTF(" %d state \r\n", g_CurrentState);
	/* Toggle LED. */
	GPIO_PortSet(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN);
	GPIO_PortClear(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN);
	GPIO_PortClear(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN);
}

void StateMachine5(void)
{
	PRINTF(" %d state \r\n", g_CurrentState);
	/* Toggle LED. */
	GPIO_PortSet(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN);
	GPIO_PortClear(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN);
	GPIO_PortSet(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN);
}

void StateMachine6(void)
{
	PRINTF(" %d state \r\n", g_CurrentState);
	/* Toggle LED. */
	GPIO_PortSet(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN);
	GPIO_PortSet(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN);
	GPIO_PortClear(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN);
}

void StateMachine7(void)
{
	PRINTF(" %d state \r\n", g_CurrentState);
	/* Toggle LED. */
	GPIO_PortSet(BOARD_LED_RED_GPIO, 1U << BOARD_LED_RED_GPIO_PIN);
	GPIO_PortSet(BOARD_LED_GREEN_GPIO, 1U << BOARD_LED_GREEN_GPIO_PIN);
	GPIO_PortSet(BOARD_LED_BLUE_GPIO, 1U << BOARD_LED_BLUE_GPIO_PIN);
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
    PRINTF("\r\n GPIO Driver example\r\n");
    PRINTF("\r\n Press %s to turn on/off a LED \r\n", BOARD_SW_NAME);

/* Init input switch GPIO. */

    GPIO_SetPinInterruptConfig(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, kGPIO_InterruptFallingEdge);
    GPIO_SetPinInterruptConfig(BOARD_SW3_GPIO, BOARD_SW3_GPIO_PIN, kGPIO_InterruptFallingEdge);

    EnableIRQ(BOARD_SW_IRQ);
    EnableIRQ(BOARD_SW3_IRQ);
    GPIO_PinInit(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, &sw_config);
    GPIO_PinInit(BOARD_SW3_GPIO, BOARD_SW3_GPIO_PIN, &sw_config);

    /* Init output LED GPIO. */
    GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);
    GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, &led_config);
    GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, &led_config);
}


/*!
 * @brief Main function
 */
int main(void)
{
	uint8_t u8Signal = (uint8_t)CondIndetermined;
	vInit();

    while (1)
    {
    	u8Signal = u8DetermineCond();

    	if(u8Signal == (uint8_t)Cond1)
    	{
    		g_CurrentState = g_StatesPtrs[g_PrevState].u8StateCond1;
    		g_ButtonPress = false;
    	}
    	else if(u8Signal == (uint8_t)Cond2)
    	{
    		g_CurrentState = g_StatesPtrs[g_PrevState].u8StateCond2;
    		g_Button2Press = false;
    	}


    	if (g_CurrentState != g_PrevState)
    	{
    		g_StatesPtrs[g_CurrentState].PtrFunc();
    		g_PrevState = g_CurrentState;
    	}
    }
}
