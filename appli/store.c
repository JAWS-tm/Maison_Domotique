
#include "headers/store.h"
#include "stm32f1_timer.h"
#include "stm32f1_motorDC.h"
#include "headers/capteurs.h"

typedef enum{
	INIT,
	GO_UP,
	GO_DOWN,
	GO_STOP,
	IN_MOVE
}storeState_e;


static motor_id_e motor_id;
static storeState_e state = INIT;
static storeWay_e storeWay = STORE_WAY_DOWN;


void STORE_init(){
	motor_id = MOTOR_add(GPIOA, GPIO_PIN_10, GPIOB, GPIO_PIN_15);
	if (motor_id == MOTOR_ID_NONE)
		printf("erreur initialisation moteur\n");
}


void STORE_process(){
	static storeState_e lastState = GO_STOP;
	bool_e entrance = (state != lastState);
	lastState = state;

	switch (state){
		case INIT:
			// Initialisation en haut

			if (entrance && CAPTEUR_up())
				MOTOR_set_duty(motor_id, STORE_WAY_UP);

			if (!CAPTEUR_up())
				state = GO_STOP;
			break;

		case GO_UP:
			if (entrance){
				MOTOR_set_duty(motor_id, STORE_WAY_UP);
				storeWay = STORE_WAY_UP;
			}

			state = IN_MOVE;
			break;

		case GO_DOWN:
			if (entrance){
				MOTOR_set_duty(motor_id, STORE_WAY_DOWN);
				storeWay = STORE_WAY_DOWN;
			}

			state = IN_MOVE;
			break;

		case IN_MOVE:
			// anti-débordement
			if ((storeWay == STORE_WAY_UP && !CAPTEUR_up()) || (storeWay == STORE_WAY_DOWN && CAPTEUR_down()))
				state = GO_STOP;

			break;

		case GO_STOP:
			if (entrance){
				MOTOR_set_duty(motor_id, STORE_WAY_STOP);
				storeWay = STORE_WAY_STOP;
			}

			break;
	}
}


void STORE_setWay(storeWay_e way) {
	switch(way) {
		case STORE_WAY_DOWN:
			state = GO_DOWN;
			break;
		case STORE_WAY_STOP:
			state = GO_STOP;
			break;
		case STORE_WAY_UP:
			state = GO_UP;
			break;
	}

}

storeStatus_e STORE_getStatus() {
	if (!CAPTEUR_up())
		return STORE_OPENED;

	else if (CAPTEUR_down())
		return STORE_CLOSED;

	else if (state == GO_STOP)
		return STORE_STOPPED;

	else
		return STORE_MOVING;
}


