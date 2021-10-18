/*
 * light.h
 *
 *  Created on: 18 oct. 2021
 *      Author: jules
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "macro_types.h"

void LIGHT_init();
void LIGHT_set_state(bool_e state);
bool_e LIGHT_get_state();

#endif /* LIGHT_H_ */
