#include "display.h"

// initialiser l'ecran : ILI9341_Init();


void DISPLAY_init(){
	ILI9341_Init();
}

void DISPLAY_test(){
	ILI9341_Fill(ILI9341_COLOR_WHITE);
	ILI9341_Puts(170,20,"bienvenu !",&Font_11x18,ILI9341_COLOR_BROWN,ILI9341_COLOR_WHITE);
	ILI9341_Puts(40,60,"temperature : ",&Font_11x18,ILI9341_COLOR_BROWN,ILI9341_COLOR_WHITE);
	ILI9341_Puts(40,90,"etat des lampes : ",&Font_11x18,ILI9341_COLOR_BROWN,ILI9341_COLOR_WHITE);
	ILI9341_Puts(40,120,"etat du volet : ",&Font_11x18,ILI9341_COLOR_BROWN,ILI9341_COLOR_WHITE);
	ILI9341_Puts(40,150,"etat de la fenetre : ",&Font_11x18,ILI9341_COLOR_BROWN,ILI9341_COLOR_WHITE);
}
