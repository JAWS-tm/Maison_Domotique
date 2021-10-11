/*
 * buttons.c
 *
 *  Created on: Oct 7, 2021
 *      Author: jules
 */
#include <stdint.h>
#include <stm32f1_gpio.h>



typedef enum {
	BUTTON_ID_LIGHT = 0,
	BUTTON_ID_STORE,
	BUTTON_ID_WINDOW,
	BUTTON_ID_NB
}button_id_e;

typedef struct {
	button_id_e button_id;
	GPIO_TypeDef GPIOx;
	uint32_t GPIO_Pin;
};


static


void BUTTONS_init(void) {
	BSP_GPIO_PinCfg(GPIOB, GPIO_PIN_9, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
}


button_id_e BUTTONS_press_event(void) {
	static bool_e previous_state[BUTTON_ID_NB] = {FALSE};
	bool_e current_state;

	for (button_id_e btn_id = 0; btn_id < BUTTON_ID_NB; btn_id++) {
		switch (btn_id) {
			case BUTTON_ID_LIGHT:
				//HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);
				break;

			case BUTTON_ID_STORE:

				break;

			case BUTTON_ID_WINDOW:

				break;

			default:
				break;
		}
	}
}
