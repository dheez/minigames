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

int updatePositions(ENTITY* player, ENTITY** ents, BULLET** bullets);
ENTITY* createEntity(int x, int y, int w, int h, int hp, int de, int wpn);
void destroyEntity(ENTITY** ents, int i);
int addEnemy(ENTITY** ents, ENTITY* e);
BULLET* createBullet(int wpn, int* dir);
void destroyBullet(BULLET** bullets, int i);
int addBullet(BULLET** bullets, BULLET* bullet);
int getDirVector(int* dir, int sx, int sy, int dx, int dy);

int renderEntities(SDL_Renderer* rend, ENTITY** entities, ENTITY* player);
