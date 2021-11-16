/*
 * light.c
 *
 *  Created on: 18 oct. 2021
 *      Author: jules
 */
#include "headers/light.h"
#include "stm32f1xx.h"
#include "stm32f1_gpio.h"
#include "WS2812S.h"

#define LED_STRIP_GPIO GPIOB
#define LED_STRIP_PIN GPIO_PIN_13

#define BLACK 0x000000
#define WHITE 0xFFFFFF

#define LED_NB 3

static bool_e light_state = FALSE;
static uint32_t general_color = 0x000000;


extern void WS2812S_send_pixel(uint32_t pixel, uint32_t gpio_pin_x, uint32_t * gpiox_bsrr);

void LIGHT_init(){
	BSP_GPIO_PinCfg(LED_STRIP_GPIO, LED_STRIP_PIN, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);
	LIGHT_set_state(FALSE);
}

void LIGHT_set_state(bool_e state) {
	light_state = state;

	uint32_t color = state ? WHITE : BLACK;

	__disable_irq();
	for(uint8_t i = 0; i < LED_NB; i++)
		WS2812S_send_pixel(color, LED_STRIP_PIN, (uint32_t *) &LED_STRIP_GPIO->BSRR);
	__enable_irq();
}

bool_e LIGHT_get_state(){
	return light_state;
}

// 0xGREEN/red/blue
void LIGHT_set_color(uint8_t r, uint8_t g, uint8_t b) {
	uint32_t color = (uint32_t) b;
	color +=((uint32_t)r)<<8;
	color += ((uint32_t)g)<<16;

	__disable_irq();
	for(uint8_t i = 0; i < LED_NB; i++)
		WS2812S_send_pixel(color, LED_STRIP_PIN, (uint32_t *) &LED_STRIP_GPIO->BSRR);
	__enable_irq();

	general_color = color;
}

void LIGHT_send_data(ledColor_t* colorsStruct) {
	uint32_t colors[LED_NB] = {0x000000};

	for (int i = 0; i < LED_NB; i++) {
		colors[i] = (uint32_t) colorsStruct[i].b;
		colors[i] +=((uint32_t) colorsStruct[i].r)<<8;
		colors[i] += ((uint32_t) colorsStruct[i].g)<<16;
	}

	__disable_irq();
	for(uint8_t i = 0; i < LED_NB; i++)
		WS2812S_send_pixel(colors[i], LED_STRIP_PIN, (uint32_t *) &LED_STRIP_GPIO->BSRR);
	__enable_irq();

}

void light_off() {
	Delay_us(100);
	HAL_GPIO_WritePin(LED_STRIP_GPIO, LED_STRIP_PIN, 0);


}
