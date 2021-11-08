
#include "store.h"

/*void STORE_init(){
	BSP_GPIO_PinCfg(CAPTEUR_up_GPIO, CAPTEUR_up_PIN, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH);

	if(CAPTEUR_down())
		while(CAPTEUR_down())
			//remonter volet
		//stop volet
			while(!CAPTEUR_down())
			//baisser volet
		//stop volet
}*/



void testPWM(){
	TIMER_enable_PWM(TIMER1_ID, TIM_CHANNEL_3, 150, FALSE, FALSE);
	TIMER_set_duty(TIMER1_ID, TIM_CHANNEL_3, /*set duty*/);
}

void set_storeState(e_storeState local){
	storeState = local;

	switch (storeState){
		case STORE_UP :
			//monter le volet
			break;
		case STORE_DOWN:
			//descendre le volet
			break;
		case STORE_STOP:
			//stoper le volet
			break;
	}
}




