/*
 * buttons.h
 *
 *  Created on: Oct 7, 2021
 *      Author: jules
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

typedef enum {
	BUTTON_ID_LIGHT = 0,
	BUTTON_ID_STORE,
	BUTTON_ID_WINDOW,
	BUTTON_ID_NB
}button_id_e;

void BUTTONS_initBtn(button_id_e button_id, GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin);

button_id_e BUTTONS_press_event(void);

#endif /* BUTTONS_H_ */
