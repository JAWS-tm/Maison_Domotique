/*
 * store.h
 *
 *  Created on: 5 oct. 2021
 */

#ifndef STORE_H_
#define STORE_H_

#include "headers/config.h"

typedef enum{
	STORE_INIT,
	STORE_UP,
	STORE_DOWN,
	STORE_STOP,
	STORE_IN_MOVE
}storeState_e;


void STORE_init();

void STORE_setState(storeState_e local);
storeState_e STORE_getState();
void STORE_process();

#endif /* STORE_H_ */