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
	STORE_UP,
	STORE_DOWN,
	STORE_STOP
}e_storeState;

e_storeState storeState;

#endif /* STORE_H_ */
