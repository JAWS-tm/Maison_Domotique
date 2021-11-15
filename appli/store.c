
#include "headers/store.h"
#include "stm32f1_timer.h"
#include "stm32f1_motorDC.h"
#include "headers/capteurs.h"

typedef enum{
	DOWN = -40,
	UP = 40
}storeWay_e;

static motor_id_e motor_id;
static storeState_e state = STORE_INIT;
static storeWay_e storeWay = DOWN;


void STORE_init(){
	motor_id = MOTOR_add(GPIOA, GPIO_PIN_10, GPIOB, GPIO_PIN_15);
	if (motor_id == MOTOR_ID_NONE)
		printf("erreur initialisation moteur\n");
}

void STORE_setState(storeState_e newState){
	if (state != STORE_INIT)
		state = newState;
}

storeState_e STORE_getState(){
	return state;
}

void STORE_process(){
	static storeState_e lastState = STORE_STOP;
	bool_e entrance = (state != lastState);
	lastState = state;

	switch (state){
		case STORE_INIT:
			// Initialisation en haut

			if (entrance && CAPTEUR_up())
				MOTOR_set_duty(motor_id, 40);


			if (!CAPTEUR_up())
				state = STORE_STOP;
			break;

		case STORE_UP:
			if (entrance){
				MOTOR_set_duty(motor_id, UP);
				storeWay = UP;
			}

			state = STORE_IN_MOVE;
			break;

		case STORE_DOWN:
			if (entrance){
				MOTOR_set_duty(motor_id, DOWN);
				storeWay = DOWN;
			}

			state = STORE_IN_MOVE;
			break;

		case STORE_IN_MOVE:
			// anti-débordement
			if ((storeWay == UP && !CAPTEUR_up()) || (storeWay == DOWN && CAPTEUR_down()))
				state = STORE_STOP;

			break;

		case STORE_STOP:
			if (entrance)
				MOTOR_set_duty(motor_id, 0);

			break;
	}




}




