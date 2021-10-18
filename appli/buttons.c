/*
 * buttons.c
 *
 *  Created on: Oct 7, 2021
 *      Author: jules
 */
#include <stdint.h>
#include <stm32f1_gpio.h>
#include "macro_types.h"
#include "buttons.h"

typedef struct {
	button_id_e button_id;
	GPIO_TypeDef * GPIOx;
	uint16_t GPIO_Pin;
}button_port_t;


static button_port_t buttons[BUTTON_ID_NB];


void BUTTONS_initBtn(button_id_e button_id, GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin) {
	buttons[button_id].GPIOx = GPIOx;
	buttons[button_id].GPIO_Pin = GPIO_Pin;

	BSP_GPIO_PinCfg(GPIOx, GPIO_Pin, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
}

//TODO: return une structure qui contient l'état de chaque bouton
button_id_e BUTTONS_press_event(void) {
	static bool_e previous_state[BUTTON_ID_NB] = {FALSE};
	bool_e current_state;
	button_id_e ret = -1;

	for (button_id_e btn_id = 0; btn_id < BUTTON_ID_NB; btn_id++) {
		current_state = HAL_GPIO_ReadPin(buttons[btn_id].GPIOx, buttons[btn_id].GPIO_Pin);
		if (current_state && !previous_state[btn_id]) {
			ret = btn_id;
		}
		previous_state[btn_id] = current_state;
	}

	return ret;
#include <stm32f1_gpio.h>
}
