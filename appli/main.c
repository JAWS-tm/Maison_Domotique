/**
  ******************************************************************************
  * @file    main.c
  * @author  Nirgal
  * @date    03-July-2019
  * @brief   Default main function.
  ******************************************************************************
*/
#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "stm32f1_adc.h"
#include "macro_types.h"
#include "systick.h"

#include "headers/photoR.h"
#include "headers/buttons.h"
#include "headers/light.h"
#include "headers/store.h"
#include "headers/capteurs.h"
#include "headers/window.h"
#include "headers/display.h"
#include "headers/auto.h"
#include "headers/scene.h"

#include "headers/fan.h"

static volatile uint32_t t = 0;
void process_ms(void)
{
	if(t)
		t--;
}


int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la premi�re �tape de la fonction main().

	HAL_Init();


	//Initialisation de l'UART2 � la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
		//Attention, les pins PA2 et PA3 ne sont pas reli�es jusqu'au connecteur de la Nucleo.
		//Ces broches sont redirig�es vers la sonde de d�bogage, la liaison UART �tant ensuite encapsul�e sur l'USB vers le PC de d�veloppement.
	//UART_init(UART1_ID,115200);

	//"Indique que les printf sortent vers le p�riph�rique UART2."
	//SYS_set_std_usart(UART1_ID, UART1_ID, UART1_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	//BSP_GPIO_PinCfg(GPIOC, GPIO_PIN_13, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//Initialisation du port du bouton bleu (carte Nucleo)
	//BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	//On ajoute la fonction process_ms � la liste des fonctions appel�es automatiquement chaque ms par la routine d'interruption du p�riph�rique SYSTICK
	Systick_add_callback_function(&process_ms);

	ADC_init();

	DISPLAY_init();

	LIGHT_init();
	SCENE_init();

	CAPTEURS_init();
	STORE_init();
	FAN_init();


	BUTTONS_initBtn(BUTTON_ID_LIGHT, GPIOB, GPIO_PIN_9);
	BUTTONS_initBtn(BUTTON_ID_STORE, GPIOB, GPIO_PIN_8);
	BUTTONS_initBtn(BUTTON_ID_WINDOW, GPIOB, GPIO_PIN_7);
	BUTTONS_initBtn(BUTTON_ID_MODE, GPIOA, GPIO_PIN_3);

	storeWay_e lastStoreWay = STORE_WAY_UP;
	windowAction_e lastWindowWay = CLOSE;

	while(1)	//boucle de t�che de fond

	{

		if(!t)
		{
			t = 10;
			switch(BUTTONS_press_event()) {
				case BUTTON_ID_LIGHT:

					debug_printf("light\n");

					SCENE_next();
					AUTO_setActive(FALSE);
					break;

				case BUTTON_ID_STORE:

					if (STORE_getStatus() == STORE_MOVING)
						STORE_setWay(STORE_WAY_STOP);
					else {
						storeWay_e newWay;
						if(lastStoreWay == STORE_WAY_DOWN)
							newWay = STORE_WAY_UP;
						else if(lastStoreWay == STORE_WAY_UP)
							newWay = STORE_WAY_DOWN;

						STORE_setWay(newWay);
						lastStoreWay = newWay;

					}
					AUTO_setActive(FALSE);

					debug_printf("store\n");
					break;

				case BUTTON_ID_WINDOW:

					if (WINDOW_getAction() == STOP){
						if (lastWindowWay == OPEN)
							WINDOW_setAction(CLOSE);
						else
							WINDOW_setAction(OPEN);
						lastWindowWay = WINDOW_getAction();
					}else
						WINDOW_setAction(STOP);

					debug_printf("window\n");
					break;
				case BUTTON_ID_MODE:

					AUTO_setActive(!AUTO_getActive());

					break;
				default:
					break;
			}

			WINDOW_process();

		}

		STORE_process();
		DISPLAY_process();
		SCENE_process();
		AUTO_process();
	}

}
