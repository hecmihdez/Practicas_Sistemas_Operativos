/*
 * StateMachine_cfg.h
 *
 *  Created on: 8 feb. 2025
 *      Author: hecto
 */

#ifndef SCHEDFIFO_CFG_H_
#define SCHEDFIFO_CFG_H_

#include "SchedFIFO.h"


#define TaskScheduler \
{  /*TaskID,			  PtrToTask,			BurstTime,			TaskState	*/ \
	{Task_ID_1,   	(PtrTask)&Task_execute,		Burst_5ms,		Task_Suspended},\
	{Task_ID_2,   	(PtrTask)&Task_execute,		Burst_10ms,		Task_Suspended},\
	{Task_ID_3,   	(PtrTask)&Task_execute,		Burst_1ms,		Task_Suspended},\
	{Task_ID_4,   	(PtrTask)&Task_execute,		Burst_2ms,		Task_Suspended},\
	{Task_ID_5,   	(PtrTask)&Task_execute,		Burst_5ms,		Task_Suspended},\
	{Task_ID_6,   	(PtrTask)&Task_execute,		Burst_1ms,		Task_Suspended},\
	{Task_ID_7,   	(PtrTask)&Task_execute,		Burst_10ms,		Task_Suspended},\
}

#endif /* SCHEDFIFO_CFG_H_ */
