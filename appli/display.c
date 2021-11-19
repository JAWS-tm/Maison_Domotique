#include "headers/display.h"
#include "headers/temperature.h"
#include "headers/auto.h"
#include "headers/store.h"
#include "headers/scene.h"
#include "headers/window.h"
#include "headers/fan.h"
#include "headers/light.h"

#include "math.h"
#include "headers/icons.h"



#define BLACK ILI9341_COLOR_BLACK
#define WHITE ILI9341_COLOR_WHITE
#define FONT &Font_11x18

#define SPACE_Y 45
#define SPACE_X 32
#define Y_OFFSET 20

void centeredText(uint16_t x, uint16_t y, char * text, bool_e clearLine);
void drawIcons();

void DISPLAY_init(){
	ILI9341_Init();
	drawIcons();
}


void drawIcons() {
	ILI9341_putImage_monochrome(BLACK, WHITE, SPACE_X, Y_OFFSET, 64, 64, store_icon, 64*64);
	ILI9341_putImage_monochrome(BLACK, WHITE, 2*SPACE_X + 64, Y_OFFSET, 64, 64, fan_icon, 64*64);
	ILI9341_putImage_monochrome(BLACK, WHITE, 3*SPACE_X + 2*64, Y_OFFSET, 64, 64, window_icon, 64*64);

	ILI9341_putImage_monochrome(BLACK, WHITE, SPACE_X, Y_OFFSET + 64 + SPACE_Y - 5, 64, 64, light_icon, 64*64);
	ILI9341_putImage_monochrome(BLACK, WHITE, 2*SPACE_X + 64, Y_OFFSET + 64 + SPACE_Y, 64, 64, thermometer_icon, 64*64);
	ILI9341_putImage_monochrome(BLACK, WHITE, 3*SPACE_X + 2*64, Y_OFFSET + 60 + SPACE_Y, 64, 64, auto_icon, 64*64);
}

void DISPLAY_process() {

	static storeStatus_e lastStoreStatus = STORE_STOPPED;
	storeStatus_e storeStatus = STORE_getStatus();
	if (storeStatus != STORE_MOVING && lastStoreStatus != storeStatus){

		char status[10];
		switch(storeStatus){
			case STORE_OPENED:
				strcpy(status, "OUVERT");
				break;
			case STORE_STOPPED:
				strcpy(status, "ARRETE");
				break;
			case STORE_CLOSED:
				strcpy(status, "FERME");
				break;
			default:
				break;

		}

		centeredText(SPACE_X + 32, Y_OFFSET + 64 + 5, status, TRUE);
		lastStoreStatus = storeStatus;
	}

	static bool_e lastFanState = TRUE;
	bool_e fanState = FAN_getState();
	if (lastFanState != fanState) {

		centeredText(2*SPACE_X + 64 + 32, Y_OFFSET + 64 + 5, fanState ? "ON" : "OFF", TRUE);
		lastFanState = fanState;
	}

	static windowAction_e lastWindowStatus = OPEN;
	windowAction_e windowStatus = WINDOW_getStatus();
	if (lastWindowStatus != windowStatus) {

		char status[10];
		switch(windowStatus){
			case OPEN:
				strcpy(status, "OUVERT");
				break;
			case STOP:
				strcpy(status, "ARRETEE");
				break;
			case CLOSE:
				strcpy(status, "FERMEE");
				break;
			default:
				break;

		}

		centeredText(3*SPACE_X + 2*64 + 32, Y_OFFSET + 64 + 5, status, TRUE);
		lastWindowStatus = windowStatus;
	}

	static scene_e lastScene = DEFAULT;
	scene_e scene = SCENE_get();
	static bool_e lastLightState = FALSE;

	if (lastScene != scene || lastLightState != LIGHT_get_state()) {

		char sceneName[10];
		if (LIGHT_get_state()) {
			strcpy(sceneName, "ON");
		}else {
			switch(scene){
				case OFF:
					strcpy(sceneName, "OFF");
					break;
				case DEFAULT:
					strcpy(sceneName, "JOUR");
					break;
				case FUTUR:
					strcpy(sceneName, "SOIREE");
					break;
				case CHILL:
					strcpy(sceneName, "CHILL");
					break;
				case DYNAMIC:
					strcpy(sceneName, "DYNAMIC");
					break;
				default:
					break;

			}
		}
		centeredText(SPACE_X + 32, Y_OFFSET + SPACE_Y + 2*64 + 5, sceneName, TRUE);
		lastScene = scene;
		lastLightState = LIGHT_get_state();
	}

	static double lastTemp = 0;
	double temperature = TEMPERATURE_get();
	if (fabs(temperature - lastTemp) >= 0.1){
		char temp[50];
		sprintf(temp, "%.1fC", temperature);
		centeredText(2*SPACE_X + 64 + 32, Y_OFFSET + SPACE_Y + 2*64 + 5, temp, FALSE);

		lastTemp = temperature;
	}

	static bool_e lastAutoActive = TRUE;
	bool_e autoActive = AUTO_getActive();
	if(lastAutoActive != autoActive){

		centeredText(3*SPACE_X + 2*64 + 32, Y_OFFSET + SPACE_Y + 2*64 + 5, autoActive ? "ON" : "OFF", TRUE);
		lastAutoActive = autoActive;
	}

	/*

	centeredText(3*SPACE_X + 2*64 + 32, Y_OFFSET + 64 + 5, "FERMEE");
	centeredText(SPACE_X + 32, Y_OFFSET + SPACE_Y + 2*64 + 5, "DYNAMIC");
	centeredText(2*SPACE_X + 64 + 32, Y_OFFSET + SPACE_Y + 2*64 + 5, "21.2C");
	centeredText(3*SPACE_X + 2*64 + 32, Y_OFFSET + SPACE_Y + 2*64 + 5, "OFF");


*/

	/*

*/
}

void centeredText(uint16_t x, uint16_t y, char * text, bool_e clearLine) {
	uint16_t width;
	ILI9341_GetStringSize(text, FONT, &width, NULL);

	if (clearLine)
		ILI9341_Puts((uint16_t) (x - 55), y, "          ", FONT, BLACK, WHITE);//clear line

	ILI9341_Puts((uint16_t) (x - (width)/2.0), y, text, FONT, BLACK, WHITE);
}


