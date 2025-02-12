/*
 * StateMachine.h
 *
 *  Created on: 8 feb. 2025
 *      Author: hecto
 */

#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

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

extern void StateMachine0(void);
extern void StateMachine1(void);
extern void StateMachine2(void);
extern void StateMachine3(void);
extern void StateMachine4(void);
extern void StateMachine5(void);
extern void StateMachine6(void);
extern void StateMachine7(void);

#endif /* STATEMACHINE_H_ */
