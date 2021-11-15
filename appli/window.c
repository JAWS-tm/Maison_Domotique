#include "headers/window.h"
#include "stm32f1_timer.h"


#define WINDOW_TIMER TIMER4_ID
#define WINDOW_CHANNEL TIM_CHANNEL_1

#define PERIOD_TIMER 10 // ms
#define MIN_DUTY 60//(1/PERIOD_TIMER) * 1000 // 1ms min duty
#define MAX_DUTY 200//(2/PERIOD_TIMER) * 1000 // 2ms max duty

#define DUTY_STEP 1 // "vitesse" et sens d'ouverture (ici 1 par actualisation)

// Servo utilisé : période de 20ms (50Hz) et duty de 1ms à 2ms
// soit de 5% à 10% de la période soit 50 à 100 dans duty


static windowAction_e actionWay = STOP;
static uint8_t servoDuty = MAX_DUTY; // fermé

void WINDOW_setAction(windowAction_e action) {
	actionWay = action;
}

windowAction_e WINDOW_getAction() {
	return actionWay;
}


void WINDOW_process() {
	typedef enum {
		INIT,
		IN_ACTION,
		WAITING_ACTION
	}state_e;

	static state_e state = INIT;

	switch (state) {
		case INIT:



			TIMER_run_us(WINDOW_TIMER, PERIOD_TIMER*1000, FALSE);

			TIMER_enable_PWM(WINDOW_TIMER, WINDOW_CHANNEL, servoDuty, FALSE, FALSE);

			state = WAITING_ACTION;
			break;

		case IN_ACTION:
			if (actionWay == STOP)
				state = WAITING_ACTION;

			if ((servoDuty <= MIN_DUTY && actionWay == OPEN) || (servoDuty >= MAX_DUTY && actionWay == CLOSE))
				actionWay = STOP;

			servoDuty += DUTY_STEP * actionWay;
			TIMER_set_duty(WINDOW_TIMER, WINDOW_CHANNEL, servoDuty);



			break;

		case WAITING_ACTION:
			if (actionWay != STOP)
				state = IN_ACTION;
			break;
	}

}
