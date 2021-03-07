#include "inv.h"
#include<math.h>

ENTITY* enemies[MAX_ENTITYS] = { NULL };
BULLET* bulletlist[MAX_BULLETS] = { NULL };

int updatePositions(ENTITY* player, ENTITY** ents, BULLET** bullets){
	//update player position
	player->hb->x += player->dir[0];
	player->hb->y += player->dir[1];
	//update enemy position
	for(int i = 0; i < MAX_ENTITYS; i++){
		ents[i]->hb->x += ents[i]->dir[0];
		ents[i]->hb->y += ents[i]->dir[1];
	}
	//update bullet position
	for(int i = 0; i < MAX_BULLETS; i++){
		bullets[i]->hb->x += bullets[i]->dir[0];
		bullets[i]->hb->y += bullets[i]->dir[1];
	}
	return 0;
}

//add enemy e to entity array
int addEnemy(ENTITY** ents, ENTITY* e){
	for(int i = 0; i < MAX_ENTITYS; i++){
		if(ents[i] == NULL){
			ents[i] = e;
			break;
		}
	}
	return 0;
}

ENTITY* createEntity(int x, int y, int hp, int de, int wpn){
	SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	rect->x = x;
	rect->y = y;
	ENTITY* e = (ENTITY*)malloc(sizeof(ENTITY));
	e->dir[0] = 0;
	e->dir[1] = 0;
	e->hb = rect;
	e->health = hp;
	e->deathevent = de;
	e->weapon = wpn;
	return e;
}

int getDirVector(int* dir, int sx, int sy, int dx, int dy){
	int x = dx - sx;
	int y = dy - sy;
	float length = sqrt((x^2) + (y^2));
	if(length >= 1){
		dir[0] = x/(int)length;
		dir[1] = y/(int)length;
	}
	else{
		printf("division by 0\n");
		return 1;
	}
	
	return 0;
}
