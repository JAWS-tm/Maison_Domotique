
#ifndef FAN_H_
#define FAN_H_

#include "macro_types.h"

void FAN_init();
void FAN_setState(bool_e state);
bool_e FAN_getState();

#endif
