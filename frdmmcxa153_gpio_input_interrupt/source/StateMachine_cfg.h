/*
 * StateMachine_cfg.h
 *
 *  Created on: 8 feb. 2025
 *      Author: hecto
 */

#ifndef STATEMACHINE_CFG_H_
#define STATEMACHINE_CFG_H_

#include "StateMachine.h"

typedef void (*StateDef)(void);

typedef enum {
    State0 = 0,
	State1,
	State2,
	State3,
	State4,
	State5,
	State6,
	State7,
    TotalStates
}enStates;

#define FunctPtr \
{	/*PtrToFunct  ,   StateCond1,    StateCond2	*/	\
	{(StateDef)&StateMachine0,   	State1, 		State7},\
	{(StateDef)&StateMachine1,   	State2, 		State0},\
	{(StateDef)&StateMachine2,   	State3, 		State1},\
	{(StateDef)&StateMachine3,   	State4, 		State2},\
	{(StateDef)&StateMachine4,   	State5, 		State3},\
	{(StateDef)&StateMachine5,   	State6, 		State4},\
	{(StateDef)&StateMachine6,   	State7, 		State5},\
	{(StateDef)&StateMachine7,   	State0, 		State6},\
}


#endif /* STATEMACHINE_CFG_H_ */
