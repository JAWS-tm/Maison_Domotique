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
#include "macro_types.h"
#include "systick.h"

#include "photoR.h"
#include "buttons.h"
#include "light.h"
#include "store.h"
<<<<<<< Updated upstream
#include "window.h"
=======
#include "display.h"
>>>>>>> Stashed changes

void writeLED(bool_e b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

bool_e readButton(void)
{
	return !HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN);
}

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



	LIGHT_init();
	CAPTEURS_init();
	STORE_init();
	DISPLAY_init();
	DISPLAY_test();

	BUTTONS_initBtn(BUTTON_ID_LIGHT, GPIOB, GPIO_PIN_9);
	BUTTONS_initBtn(BUTTON_ID_STORE, GPIOB, GPIO_PIN_8);
	/*BUTTONS_initBtn(BUTTON_ID_WINDOW, GPIOB, GPIO_PIN_7);*/


	storeState_e lastStoreWay = STORE_DOWN;
	windowAction_e lastAction = STOP;
	while(1)	//boucle de t�che de fond

	{

		if(!t)
		{

			t = 10;
			switch(BUTTONS_press_event()) {
				case BUTTON_ID_LIGHT:

					printf("light\n");
					LIGHT_set_state(!LIGHT_get_state());



					break;
				case BUTTON_ID_STORE:
					if (STORE_getState() == STORE_IN_MOVE)
						STORE_setState(STORE_STOP);
					else if(STORE_getState() == STORE_STOP){
						if(lastStoreWay == STORE_DOWN)
							STORE_setState(STORE_UP);
						else if(lastStoreWay == STORE_UP)
							STORE_setState(STORE_DOWN);

						lastStoreWay = STORE_getState();
					}
					break;
				case BUTTON_ID_WINDOW:


					if (WINDOW_getAction() == STOP)
						if (lastAction == OPEN)
							WINDOW_setAction(CLOSE);
						else
							WINDOW_setAction(OPEN);
					else
						WINDOW_setAction(STOP);


					printf("window\n");
					break;
				default:
					break;
			}


		}
		WINDOW_process();
		STORE_process();
		/*printf("valeur photo-resistance intertieur , %d",PHOTO_R_getValue(INT));
		if(PHOTO_R_getValue(INT) > 2700)
			LIGHT_set_state(TRUE);
		else
			LIGHT_set_state(FALSE);*/

	}
}
