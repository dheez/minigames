#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#define MAX_BULLETS 100
#define MAX_ENTITYS 20
#define ITEM_CAP 3

typedef struct item{
	int type;
	void* effects;
}ITEM;

typedef struct bullet{
	SDL_Rect hb;
	int dmg;
	int dir[2];
}BULLET;

typedef struct entity{
	SDL_Rect hb;
	int dir[2], atk, health;
	ITEM* items[ITEM_CAP];
	int deathevent;
}ENTITY;

