//#include "capteurs.h"
#include "stm32f1xx.h"
#include "macro_types.h"
#include "stm32f1_gpio.h"

#define CAPTEUR_up_GPIO GPIOB
#define CAPTEUR_up_PIN GPIO_PIN_0

#define CAPTEUR_down_GPIO GPIOB
#define CAPTEUR_down_PIN GPIO_PIN_1

void CAPTEURS_init(){
	BSP_GPIO_PinCfg(CAPTEUR_up_GPIO, CAPTEUR_up_PIN, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
	BSP_GPIO_PinCfg(CAPTEUR_down_GPIO, CAPTEUR_down_PIN, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
}


bool_e CAPTEUR_up(){
	return !HAL_GPIO_ReadPin(CAPTEUR_up_GPIO, CAPTEUR_up_PIN);

}

bool_e CAPTEUR_down(){
	return !HAL_GPIO_ReadPin(CAPTEUR_down_GPIO, CAPTEUR_down_PIN);

}
