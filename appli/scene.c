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
			//static uint32_t* dynamicColors = {0xff0000, 0x00ff00, 0x0000ff};
			/*if (entrance)
				dynamicColors = {0xff0000, 0x00ff00, 0x0000ff};*/




			if (goToNextScene){
				scene = OFF;
				goToNextScene = FALSE;
			}
			break;

	}

}
