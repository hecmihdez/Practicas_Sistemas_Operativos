#include "fsl_debug_console.h"
#include "board.h"
#include "app.h"
#include "fsl_ctimer.h"
#include "fsl_sctimer.h"
#include "servo_task.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef CTIMER_MAT_PWM_PERIOD_CHANNEL
#define CTIMER_MAT_PWM_PERIOD_CHANNEL kCTIMER_Match_3
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
uint32_t timerClock;
volatile uint32_t g_pwmPeriod   = 0U;
volatile uint32_t g_pulsePeriod = 0U;
extern QueueHandle_t servo_queue;
static uint32_t event;

#define CLOSESERVO   0
#define OPENSERVO    1

#define APP_BOARD_TEST_LED_PORT BOARD_LED_BLUE_GPIO_PORT
#define APP_BOARD_TEST_LED_PIN  BOARD_LED_BLUE_GPIO_PIN
#define APP_BOARD_TEST_LED_GREEN_PIN  12U
#define APP_BOARD_TEST_LED_RED_PIN  1U
/*******************************************************************************
 * Code
 ******************************************************************************/
status_t CTIMER_GetPwmPeriodValue(uint32_t pwmFreqHz, uint8_t dutyCyclePercent, uint32_t timerClock_Hz)
{
    /* Calculate PWM period match value */
    g_pwmPeriod = (timerClock_Hz / pwmFreqHz) - 1U;

    /* Calculate pulse width match value */
    g_pulsePeriod = (g_pwmPeriod + 1U) * (100 - dutyCyclePercent) / 100;

    return kStatus_Success;
}

void init_pwm()
{
    ctimer_config_t config;
    uint32_t srcClock_Hz;

    /* CTimer0 counter uses the AHB clock, some CTimer1 modules use the Aysnc clock */
    srcClock_Hz = CTIMER_CLK_FREQ;

    PRINTF("CTimer example to generate a PWM signal\r\n");

    CTIMER_GetDefaultConfig(&config);
    timerClock = srcClock_Hz / (config.prescale + 1);

    CTIMER_Init(CTIMER, &config);

    /* Get the PWM period match value and pulse width match value of 20Khz PWM signal with 20% dutycycle */
    CTIMER_GetPwmPeriodValue(50, (uint8_t)DUTY_CYCLE_20, timerClock);
    CTIMER_SetupPwmPeriod(CTIMER, CTIMER_MAT_PWM_PERIOD_CHANNEL, CTIMER_MAT_OUT, g_pwmPeriod, g_pulsePeriod, false);
    CTIMER_StartTimer(CTIMER);
}

//void init_pwm(void)
//{
//	uint8_t u8State = 0U;
//    sctimer_config_t sctimerInfo;
//    sctimer_pwm_signal_param_t pwmParam;
//    uint32_t sctimerClock;
//
//    sctimerClock = CTIMER_CLK_FREQ;
//
//    SCTIMER_GetDefaultConfig(&sctimerInfo);
//
//    /* Initialize SCTimer module */
//    SCTIMER_Init(SCT0, &sctimerInfo);
//
//    /* Configure first PWM with frequency 24kHZ from first output */
//    pwmParam.output           = DEMO_FIRST_SCTIMER_OUT;
//    pwmParam.level            = kSCTIMER_HighTrue;
//    pwmParam.dutyCyclePercent = 10;
//    if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_CenterAlignedPwm, 50, sctimerClock, &event) == kStatus_Fail)
//    {
//    	u8State = 1U;
//    }
//    else
//    {
//    	/* Start the 32-bit unify timer */
//    	SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_U);
//    }
//
////    return u8State;
//}

void move_Servo(char value)
{

	//Stop PWM signel before changing
	CTIMER_StopTimer(CTIMER);

	//Configure with new value depending on the parameter
	if (value == OPENSERVO)
	{
		/* Get the PWM period match value and pulse width match value of 50hz PWM signal with 20% dutycycle */
		CTIMER_GetPwmPeriodValue(50, (uint8_t)5, timerClock);
	}
	else
	{
		/* Get the PWM period match value and pulse width match value of 50hz PWM signal with 90% dutycycle */
		CTIMER_GetPwmPeriodValue(50, (uint8_t)10, timerClock);
	}
    CTIMER_SetupPwmPeriod(CTIMER, CTIMER_MAT_PWM_PERIOD_CHANNEL, CTIMER_MAT_OUT, g_pwmPeriod, g_pulsePeriod, false);
    CTIMER_StartTimer(CTIMER);
}

//void move_Servo(char value)
//{
//
//	//Stop PWM signel before changing
//	//CTIMER_StopTimer(CTIMER);
////	SCTIMER_StopTimer(SCT0, kSCTIMER_Counter_U);
//
//	//Configure with new value depending on the parameter
//	if (value == OPENSERVO)
//	{
//		/* Get the PWM period match value and pulse width match value of 50hz PWM signal with 20% dutycycle */
//		SCTIMER_UpdatePwmDutycycle(SCT0, DEMO_FIRST_SCTIMER_OUT, 5, event);
//	}
//	else
//	{
//		/* Get the PWM period match value and pulse width match value of 50hz PWM signal with 90% dutycycle */
//		SCTIMER_UpdatePwmDutycycle(SCT0, DEMO_FIRST_SCTIMER_OUT, 10, event);
//	}
////    CTIMER_SetupPwmPeriod(CTIMER, CTIMER_MAT_PWM_PERIOD_CHANNEL, CTIMER_MAT_OUT, g_pwmPeriod, g_pulsePeriod, false);
////    CTIMER_StartTimer(CTIMER);
//
////	SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_U);
//}

void ServoTask(void *param)
{
    char cmd[2 + 1];

    init_pwm();

//    while (1)
//    {
		while (1) //TODO wait for new messages on servo_queue using xQueueReceive
		{
			if (xQueueReceive(servo_queue, cmd, portMAX_DELAY) == pdTRUE)
			{
				switch (cmd[0])
				{
					case 'o':
						PRINTF("Open servo\r\n");
						GPIO_PinWrite(GPIO, APP_BOARD_TEST_LED_PORT, APP_BOARD_TEST_LED_PIN, 1U);
						GPIO_PinWrite(GPIO, APP_BOARD_TEST_LED_PORT, APP_BOARD_TEST_LED_GREEN_PIN, 0U);
						GPIO_PinWrite(GPIO, APP_BOARD_TEST_LED_PORT, APP_BOARD_TEST_LED_RED_PIN, 1U);
						move_Servo (OPENSERVO);
						vTaskDelay(1000);
						PRINTF("Closing servo...\r\n");
						move_Servo (CLOSESERVO);
						GPIO_PinWrite(GPIO, APP_BOARD_TEST_LED_PORT, APP_BOARD_TEST_LED_PIN, 1U);
						GPIO_PinWrite(GPIO, APP_BOARD_TEST_LED_PORT, APP_BOARD_TEST_LED_GREEN_PIN, 1U);
						GPIO_PinWrite(GPIO, APP_BOARD_TEST_LED_PORT, APP_BOARD_TEST_LED_RED_PIN, 1U);
					break;
					case 'c':
						PRINTF("Close servo\r\n");
						move_Servo (CLOSESERVO);
					break;
					default:
					break;
				}
			}
		}

//    }
}
