#include "inv.h"

MAP* maps[MAX_MAPS];

MAP* testMap(void){
	MAP* test = (MAP*)malloc(sizeof(MAP));
	SDL_Rect rect1 = {.x=-960,.y=200,.w=1920,.h=500};
	test->world[0] = &rect1;
	return test;
}

int addMap(MAP** maps, Map* map){
	for(int i = 0; i < MAX_MAPS; i++){
		if(maps[i] == NULL){
			maps[i] = map;
			return 0;
		}
	}
	return 1;
}
void freeMap(MAP* m){
	for(int i = 0; i < MAX_WORLD_BLOCKS; i++){
		if(world[i] != NULL){
			free(world[i]);
		}
		if(visible[i] != NULL){
			free(visible[i]);
		}
	}
}
