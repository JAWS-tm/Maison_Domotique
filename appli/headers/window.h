
#ifndef WINDOW_H_
#define WINDOW_H_

#include "stm32f1_timer.h"
#include "headers/config.h"

typedef enum {
	OPEN = -1,
	STOP,
	CLOSE,
}windowAction_e;

void WINDOW_setAction(windowAction_e action);

windowAction_e WINDOW_getStatus();
windowAction_e WINDOW_getAction();

void WINDOW_process();

#endif
