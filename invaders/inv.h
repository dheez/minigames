#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#define MAX_BULLETS 100
#define MAX_ENTITYS 20
#define MAX_WORLD_BLOCKS 500
#define MAX_MAPS 3
#define ITEM_CAP 3

typedef struct item{
	int type;
	void* effects;
}ITEM;

typedef struct bullet{
	SDL_Rect* hb;
	int dmg, dir[2];
}BULLET;

typedef struct entity{
	SDL_Rect* hb, wpn;
	int dir[2], reldir[2], atk, health, deathevent, weapon;
	ITEM* items[ITEM_CAP];
}ENTITY;

typedef struct map{
	SDL_Rect* world[MAX_WORLD_BLOCKS];
	SDL_Rect* visible[MAX_WORLD_BLOCKS];
}MAP;

