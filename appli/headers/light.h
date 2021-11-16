/*
 * light.h
 *
 *  Created on: 18 oct. 2021
 *      Author: jules
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "macro_types.h"

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
}ledColor_t;


void LIGHT_init();
void LIGHT_set_state(bool_e state);
bool_e LIGHT_get_state();

void LIGHT_set_color(uint8_t r, uint8_t g, uint8_t b); // TODO : ledColor_t
void LIGHT_send_data(ledColor_t* colors);

#endif /* LIGHT_H_ */
