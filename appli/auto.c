#include "headers/auto.h"
#include "headers/capteurs.h"
#include "headers/store.h"
#include "headers/photoR.h"
#include "headers/light.h"

typedef enum{
	LOWLIGHT,
	LIGHT_STATE,
	HIGHTLIGHT
}state_e;

static state_e state = LIGHT_STATE;
static bool_e entrence = FALSE;


void AUTO_process(){

	switch(state){
		case LIGHT_STATE:
			if(PHOTO_R_getValue(INTERIOR) < 1000 && LIGHT_get_state()==FALSE)
				state = LOWLIGHT;
			else if(PHOTO_R_getValue(INTERIOR) > 1000)
				LIGHT_set_state(FALSE);
			else
				STORE_setState(STORE_STOP);

			if(PHOTO_R_getValue(INTERIOR) > 3000 && LIGHT_get_state()==FALSE)
				state = HIGHTLIGHT;
			else if(LIGHT_get_state())
				LIGHT_set_state(FALSE);
			break;
		case LOWLIGHT:
			if(CAPTEUR_down() && !entrence){
				STORE_setState(STORE_UP);
				entrence = TRUE;
			}
			if(!CAPTEUR_up()){
				entrence = FALSE;
			//if(!CAPTEUR_up() && !entrence)
				LIGHT_set_state(TRUE);
			}
			state = LIGHT_STATE;
			break;

		case HIGHTLIGHT:
			if(!CAPTEUR_up() && !entrence){
				STORE_setState(STORE_DOWN);
				entrence = TRUE;
			}
			if(CAPTEUR_down()){
				entrence = FALSE;

			}
			state = LIGHT_STATE;
			break;

	}

	/*if(PHOTO_R_getValue(INTERIOR) < 2700 && CAPTEUR_down()){
		STORE_setState(STORE_UP);
		if(PHOTO_R_getValue(INTERIOR) < 2700)
			LIGHT_set_state(TRUE);
	}

	if()
		LIGHT_set_state(TRUE);

	if((PHOTO_R_getValue(INTERIOR) < PHOTO_R_getValue(EXTERIOR)) && STORE_getState()== STORE_DOWN)
		STORE_setState(STORE_UP);
	if()*/
}

