/*
 * store.h
 *
 *  Created on: 5 oct. 2021
 */

#ifndef STORE_H_
#define STORE_H_

#include "headers/config.h"

typedef enum{
	STORE_WAY_DOWN = -40,
	STORE_WAY_STOP = 0,
	STORE_WAY_UP = 40
}storeWay_e;

typedef enum {
	STORE_OPENED,
	STORE_STOPPED,
	STORE_CLOSED,
	STORE_MOVING
}storeStatus_e;

void STORE_init();

storeStatus_e STORE_getStatus();

void STORE_process();

#endif /* STORE_H_ */
