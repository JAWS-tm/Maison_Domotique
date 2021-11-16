#include "headers/scene.h"
#include "headers/light.h"
#include "systick.h"
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

static ledColor_t dynamicColors[3];


static uint32_t t = 0;
void process_delay() {
	if (t)
		t--;
}

void SCENE_init(){
	Systick_add_callback_function(&process_delay);
}

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
				LIGHT_set_color(255, 200, 0);

			if (goToNextScene){
				scene = CHILL;
				goToNextScene = FALSE;
			}
			break;
		case CHILL:
			if (entrance)
				LIGHT_send_data((ledColor_t[]) {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}});

			if (goToNextScene){
				scene = DYNAMIC;
				goToNextScene = FALSE;
			}
			break;

		case DYNAMIC:

			if (entrance) {
				dynamicColors[0] = (ledColor_t) {255, 0, 0};
				dynamicColors[1] = (ledColor_t) {125, 255, 0};
				dynamicColors[2] = (ledColor_t) {0, 125, 255};
				//colorDynamic = (color_t) {255, 0, 0};
				t = 10;
			}

			if (!t){
				t = 10;
				for (int i = 0; i < 3; i++) {
					if (dynamicColors[i].r == 255 && dynamicColors[i].g < 255 && dynamicColors[i].b == 0)
						dynamicColors[i].g++;
					else if (dynamicColors[i].r > 0 && dynamicColors[i].g == 255 && dynamicColors[i].b == 0)
						dynamicColors[i].r--;
					else if (dynamicColors[i].r == 0 && dynamicColors[i].g == 255 && dynamicColors[i].b < 255)
						dynamicColors[i].b++;
					else if (dynamicColors[i].r == 0 && dynamicColors[i].g > 0 && dynamicColors[i].b == 255)
						dynamicColors[i].g--;
					else if (dynamicColors[i].r < 255 && dynamicColors[i].g == 0 && dynamicColors[i].b == 255)
						dynamicColors[i].r++;
					else if (dynamicColors[i].r == 255 && dynamicColors[i].g == 0 && dynamicColors[i].b > 0)
						dynamicColors[i].b--;
				}


				LIGHT_send_data(dynamicColors);//(colorDynamic.r, colorDynamic.g, colorDynamic.b);
			}

			if (goToNextScene){
				scene = FUTUR;
				goToNextScene = FALSE;
			}
			break;
		case FUTUR:
			if (entrance)
				LIGHT_send_data((ledColor_t[]) {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}});

			if (goToNextScene){
				scene = OFF;
				goToNextScene = FALSE;
			}
			break;
	}


}
