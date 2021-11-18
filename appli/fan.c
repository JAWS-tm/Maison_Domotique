#include "headers/fan.h"
#include "stm32f1xx.h"
#include "stm32f1_gpio.h"

#define FAN_GPIO GPIOB
#define FAN_PIN GPIO_PIN_5

static bool_e active = FALSE;

void FAN_init() {
	BSP_GPIO_PinCfg(FAN_GPIO, FAN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);
}

void FAN_setState(bool_e state) {
	debug_printf("ventilo : %d", state);
	HAL_GPIO_WritePin(FAN_GPIO, FAN_PIN, state);
	active = state;
}

bool_e FAN_getState(){
	return active;
}
