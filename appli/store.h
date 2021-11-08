/*
 * store.h
 *
 *  Created on: 5 oct. 2021
 *      Author: hugo
 */

#ifndef STORE_H_
#define STORE_H_

#include "stm32f1_timer.h"
#include "config.h"

typedef enum{
	STORE_INIT,
	STORE_UP,
	STORE_DOWN,
	STORE_STOP
}storeState_e;


void STORE_init();

void STORE_setState(storeState_e local);
void STORE_process();

#endif /* STORE_H_ */
