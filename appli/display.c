#include "headers/display.h"
#include "headers/temperature.h"
#include "headers/auto.h"

#include "stdlib.h"

void DISPLAY_init(){
	ILI9341_Init();
}

void DISPLAY_test(){
	ILI9341_Fill(ILI9341_COLOR_WHITE);
	ILI9341_Puts(70,20,"bienvenu !",&Font_11x18,ILI9341_COLOR_BROWN,ILI9341_COLOR_WHITE);
	ILI9341_Puts(40,60,"temperature : ",&Font_11x18,ILI9341_COLOR_BROWN,ILI9341_COLOR_WHITE);
	ILI9341_Puts(40,90,"etat des lampes : ",&Font_11x18,ILI9341_COLOR_BROWN,ILI9341_COLOR_WHITE);
	ILI9341_Puts(40,120,"etat du volet : ",&Font_11x18,ILI9341_COLOR_BROWN,ILI9341_COLOR_WHITE);
	ILI9341_Puts(40,150,"etat de la fenetre : ",&Font_11x18,ILI9341_COLOR_BROWN,ILI9341_COLOR_WHITE);
}

#include "macro_types.h"

void DISPLAY_process() {
	static double lastTemp = 0;
	double temperature = TEMPERATURE_get();

	if (temperature != -1 && abs((int8_t) ((temperature - lastTemp) * 10)) >= 5){ // >= 0.5
		char str[50];
		sprintf(str, "temperature : %f", temperature);
		ILI9341_Puts(40,60,str,&Font_11x18,ILI9341_COLOR_RED,ILI9341_COLOR_WHITE);
		lastTemp = temperature;
	}

	static double lastMode = 0;
	double mode = AUTO_getActive();

}
