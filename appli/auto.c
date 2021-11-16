#include "headers/auto.h"
#include "headers/capteurs.h"
#include "headers/store.h"
#include "headers/photoR.h"
#include "headers/light.h"

typedef enum{
	INIT,
	LOWLIGHT,
	LIGHT_STATE,
	HIGHTLIGHT
}state_e;

static state_e state = INIT;
static bool_e entrence = FALSE;

static bool_e active = FALSE;

void AUTO_setActive(bool_e state)
{
	active = state;
}

bool_e AUTO_getActive() {
	return active;
}

void AUTO_process(){
	if (!active)
		return;

	switch(state){

		case INIT:
			LIGHT_set_state(FALSE);
			state = LIGHT_STATE;
			break;

		case LIGHT_STATE:
			if(PHOTO_R_getValue(INTERIOR) < 1000)
				state = LOWLIGHT;

			else if(PHOTO_R_getValue(INTERIOR) > 2700)
				state = HIGHTLIGHT;

			else
				STORE_setState(STORE_STOP);

			break;

		case LOWLIGHT:
			if(CAPTEUR_up() && LIGHT_get_state()==FALSE){
				STORE_setState(STORE_UP);
			}
			else if(!CAPTEUR_up() && LIGHT_get_state()==FALSE){
				LIGHT_set_state(TRUE);
			}
			state = LIGHT_STATE;
			break;

		case HIGHTLIGHT:
			if (!CAPTEUR_down()){
				if (LIGHT_get_state())
					LIGHT_set_state(FALSE);
				else
					STORE_setState(STORE_DOWN);
			}



			state = LIGHT_STATE;
			break;

	}

}

