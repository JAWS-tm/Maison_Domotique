
#include "store.h"
#include "stm32f1_timer.h"
#include "stm32f1_motorDC.h"
#include "capteurs.h"

#define PWM_FIN_TIMER_ID TIMER1_ID
#define PWM_FIN_TIMER_CHANNEL TIM_CHANNEL_3

#define PWM_RIN_TIMER_ID TIMER1_ID
#define PWM_RIN_TIMER_CHANNEL TIM_CHANNEL_3


static motor_id_e motor_id;

static storeState_e storeState = STORE_INIT;

void STORE_init(){
	motor_id = MOTOR_add(GPIOA, GPIO_PIN_10, GPIOB, GPIO_PIN_15);
	if (motor_id == MOTOR_ID_NONE)
		printf("erreur moteur");
}

void STORE_setState(storeState_e state){
	storeState = state;

	switch (state){
		case STORE_INIT:
			if (CAPTEUR_down())
				MOTOR_set_duty(motor_id, 40);
			else
				MOTOR_set_duty(motor_id, -40);
			break;
		case STORE_UP:
			MOTOR_set_duty(motor_id, 40);
			break;
		case STORE_DOWN:
			MOTOR_set_duty(motor_id, -40);
			break;
		case STORE_STOP:
			MOTOR_set_duty(motor_id, 0);
			break;
	}
}

storeState_e STORE_getState(){
	return storeState;
}

void STORE_process(){
	if (storeState == STORE_UP && !CAPTEUR_up())
		STORE_setState(STORE_STOP);
	else if (storeState == STORE_DOWN && CAPTEUR_down())
		STORE_setState(STORE_STOP);
}




