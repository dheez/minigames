#include "inv.h"
#include<math.h>

//ENTITY* enemies[MAX_ENTITYS] = { NULL };
//BULLET* bulletlist[MAX_BULLETS] = { NULL };

//update positions of entities and players and bullets per iteration
int updatePositions(ENTITY* player, ENTITY** ents, BULLET** bullets){
	//update player position
	if(player != NULL){
		player->hb->x += player->dir[0];
		player->hb->y += player->dir[1];
		player->mid->x += player->dir[0];
		player->mid->y += player->dir[1];
	}
	//update enemy position
	for(int i = 0; i < MAX_ENTITYS; i++){
		if(ents[i] != NULL){
			ents[i]->hb->x += ents[i]->dir[0];
			ents[i]->hb->y += ents[i]->dir[1];
			ents[i]->mid->x += ents[i]->dir[0];
			ents[i]->mid->y += ents[i]->dir[1];
		}
		
	}
	//update bullet position
	for(int i = 0; i < MAX_BULLETS; i++){
		if(bullets[i] != NULL){
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
			return 0;
		}
	}
	return 1;
}
//entity "constructor"
ENTITY* createEntity(int x, int y,int w, int h, int hp, int de, int wpn){
	SDL_Rect* rect = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	ENTITY* e = (ENTITY*)malloc(sizeof(ENTITY));
	e->dir[0] = 0;
	e->dir[1] = 0;
	e->hb = rect;
	e->mid = getmid(e->hb);
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
	SDL_Rect* b = malloc(sizeof(SDL_Rect));
	bullet->hb = b;
	int mult = 1;
	switch(wpn){
		case 0:
			bullet->dmg = 5;
			bullet->hb->w = 10;
			bullet->hb->h = 10;
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

int ggT(int a, int b){
	if(b == 0){
		return a;
	}
	return ggT(b,a%b);
}

int getDirVector(int* dir, int sx, int sy, int dx, int dy){
	int x = dx - sx;
	int y = dy - sy;
	int gcd = ggT(x,y);
	dir[0] = x / gcd;
	dir[1] = y / gcd;
	return 0;
}

SDL_Point* getmid(SDL_Rect* rect){
	SDL_Point* p = malloc(sizeof(SDL_Point));
	p->x = rect->x + rect->w/2;
	p->y = rect->y + rect->h/2;
	return p;
}

int shoot(ENTITY* e, SDL_Point* p, BULLET** bulletlist){
	int dir[2];
	SDL_Point* m = getmid(e->hb);
	getDirVector(dir,m->x,m->y,p->x,p->y);
	BULLET* b = createBullet(0,dir);
	b->hb->x = m->x + dir[0];
	b->hb->y = m->y + dir[1];
	addBullet(bulletlist,b);
	return 0;
}
