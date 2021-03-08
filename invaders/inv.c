#include "inv.h"
#include<math.h>

ENTITY* enemies[MAX_ENTITYS] = { NULL };
BULLET* bulletlist[MAX_BULLETS] = { NULL };

//update positions of entities and players and bullets per iteration
int updatePositions(ENTITY* player, ENTITY** ents, BULLET** bullets, MAP* m){
	//update player position
	if(player != NULL){
		player->hb->x += player->dir[0];
		player->hb->y += player->dir[1];
	}
	//update enemy position
	for(int i = 0; i < MAX_ENTITYS; i++){
		if(ents[i] != NULL){
			ents[i]->hb->x += ents[i]->dir[0];
			ents[i]->hb->y += ents[i]->dir[1];
		}
		
	}
	//update bullet position
	for(int i = 0; i < MAX_BULLETS; i++){
		if(ents[i] != NULL){
			bullets[i]->hb->x += bullets[i]->dir[0];
			bullets[i]->hb->y += bullets[i]->dir[1];
		}
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
//entity "constructor"
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
//destructor
void destroyEntity(ENTITY** ents, int i){
	if(ents[i] != NULL){
		free(ents[i]);
		ents[i] = NULL;
	}
}

int addBullet(BULLET** bullets, BULLET* bullet){
	for(int i = 0; i < MAX_BULLETS; i++){
		if(bullets[i] == NULL){
			bullets[i] = bullet;
			return 0;
		}
	}
	return 1;
}

BULLET* createBullet(int wpn, int* dir){
	BULLET* bullet = (BULLET*)malloc(sizeof(BULLET));
	int mult = 1;
	switch(wpn){
		case 0:
			break;
		case 1:
			break;
	}
	bullet->dir[0] = mult*dir[0];
	bullet->dir[1] = mult*dir[1];
	return bullet;
}

void destroyBullet(BULLET** bullets, int i){
	if(bullets[i] != NULL){
		free(bullets[i]);
		bullets[i] = NULL;
	}
	
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
