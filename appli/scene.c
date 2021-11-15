#include "headers/scene.h"
#include "headers/light.h"

/*
typedef struct {
	uint32_t color[3];
	char name[20];
}scene_t;
*/

static bool_e goToNextScene = FALSE;

void SCENE_next(){
	goToNextScene = TRUE;
}

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;

}color_t;

static color_t dynamicColors[3];

static color_t colorDynamic;

void SCENE_process() {
	typedef enum {
		OFF,
		DEFAULT,
		CHILL,
		FUTUR,
		DYNAMIC
	} scene_e;

	static scene_e scene = DEFAULT;
	static scene_e lastScene = DYNAMIC;

	bool_e entrance = (scene != lastScene);

	lastScene = scene;

	switch(scene) {
		case OFF:
			if (entrance)
				LIGHT_set_state(FALSE);

			if (goToNextScene){
				scene = DEFAULT;
				goToNextScene = FALSE;
			}

			break;
		case DEFAULT:
			if (entrance)
				LIGHT_set_color(255,255,150);

			if (goToNextScene){
				scene = CHILL;
				goToNextScene = FALSE;
			}
			break;
		case CHILL:
			if (entrance)
				LIGHT_send_data((uint32_t[]) {0xffcc54, 0xffd5ad, 0xd8ffba});

			if (goToNextScene){
				scene = FUTUR;
				goToNextScene = FALSE;
			}
			break;
		case FUTUR:
			if (entrance)
				LIGHT_send_data((uint32_t[]) {0x9f40ff, 0x3798fa, 0x31e0cc});

			if (goToNextScene){
				scene = DYNAMIC;
				goToNextScene = FALSE;
			}
			break;
		case DYNAMIC:

			if (entrance) {
				dynamicColors[0] = (color_t) {255, 0, 0};
				dynamicColors[1] = (color_t) {255, 0, 0};
				dynamicColors[2] = (color_t) {255, 0, 0};
				colorDynamic = (color_t) {255, 0, 0};
			}

			if (colorDynamic.r == 255 && colorDynamic.g < 255 && colorDynamic.b == 0)
				colorDynamic.g++;
			else if (colorDynamic.r > 0 && colorDynamic.g == 255 && colorDynamic.b == 0)
				colorDynamic.r--;
			else if (colorDynamic.r == 0 && colorDynamic.g == 255 && colorDynamic.b < 255)
				colorDynamic.b++;
			else if (colorDynamic.r == 0 && colorDynamic.g > 0 && colorDynamic.b == 255)
				colorDynamic.g++;
			else if (colorDynamic.r < 255 && colorDynamic.g == 0 && colorDynamic.b == 255)
				colorDynamic.r++;
			else if (colorDynamic.r == 255 && colorDynamic.g == 0 && colorDynamic.b > 0)
				colorDynamic.b--;

			LIGHT_set_color(colorDynamic.r,colorDynamic.g,colorDynamic.b);

			if (goToNextScene){
				scene = OFF;
				goToNextScene = FALSE;
			}
			break;

	}

}
