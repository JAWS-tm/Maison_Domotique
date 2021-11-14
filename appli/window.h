
#ifndef WINDOW_H_
#define WINDOW_H_

#include "stm32f1_timer.h"
#include "config.h"

typedef enum {
	CLOSE = -1,
	STOP,
	OPEN,
}windowAction_e;

void WINDOW_setAction(windowAction_e action);

windowAction_e WINDOW_getAction();

void WINDOW_process();

#endif
