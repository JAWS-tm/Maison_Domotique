
#ifndef SCENE_H_
#define SCENE_H_

typedef enum {
	OFF,
	DEFAULT,
	CHILL,
	FUTUR,
	DYNAMIC
} scene_e;

void SCENE_init();
void SCENE_process();
void SCENE_next();
scene_e SCENE_get();

#endif

