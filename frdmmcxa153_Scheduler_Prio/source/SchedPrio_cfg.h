/*
 * StateMachine_cfg.h
 *
 *  Created on: 8 feb. 2025
 *      Author: hecto
 */

#ifndef SCHEDPRIO_CFG_H_
#define SCHEDPRIO_CFG_H_

#include "SchedPrio.h"


#define TaskScheduler \
{  /*TaskID,			  PtrToTask,					Priority,			TaskState	*/ \
	{Task_ID_1,   	(PtrTask)&Task_execute,					2,			Task_Suspended},\
	{Task_ID_2,   	(PtrTask)&Task_execute,		   			2,			Task_Suspended},\
	{Task_ID_3,   	(PtrTask)&Task_execute,					2,			Task_Suspended},\
	{Task_ID_4,   	(PtrTask)&Task_execute,					2,			Task_Suspended},\
	{Task_ID_5,   	(PtrTask)&Task_execute,					2,			Task_Suspended},\
	{Task_ID_6,   	(PtrTask)&Task_execute,					2,			Task_Suspended},\
	{Task_ID_7,   	(PtrTask)&Task_execute,					2,			Task_Suspended},\
	{Task_ID_HPrio, (PtrTask)&Task_execute_HighPrio,		1,			Task_Suspended},\
}

#endif /* SCHEDPRIO_CFG_H_ */
