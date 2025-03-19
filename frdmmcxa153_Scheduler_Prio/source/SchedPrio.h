/*
 * StateMachine.h
 *
 *  Created on: 8 feb. 2025
 *      Author: hecto
 */

#ifndef SCHEDPRIO_H_
#define SCHEDPRIO_H_

typedef void (*PtrTask)(uint8_t);

typedef enum {
    Task_ID_1 = 1,
	Task_ID_2,
	Task_ID_3,
	Task_ID_4,
	Task_ID_5,
	Task_ID_6,
	Task_ID_7,
    TotalTasks
}enTaskIds;

typedef enum {
	Task_Suspended = 0,
	Task_Ready,
	Task_Running,
	Total_States
}enTaskStates;

extern void Task_execute(uint8_t u8TaskId);

#endif /* SCHEDPRIO_H_ */
