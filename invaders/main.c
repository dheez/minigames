#include "inv.h"
#include<time.h>

int main(void){

	if(SDL_Init(SDL_INIT_VIDEO)!= 0){
		printf("error initializing video\n");
		SDL_Quit();
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow("Invaders",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1920,1080,0);
	if(win == NULL){
		printf("error creating window\n");
		SDL_Quit();
		return 1;
	}
	
	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
	if(!rend){
		printf("couldn't create renderer\n");
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}

	SDL_Cursor* cursor = SDL_GetCursor();
	if(!cursor){
		printf("couldn't create cursor\n");
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	
	SDL_RenderClear(rend);
	SDL_RenderPresent(rend);

	SDL_Event e;
	int quit = 0;
	ENTITY* player = createEntity(100,800,50,90,100,1,0);
	ENTITY* bot1 = createEntity(1700, 100,50,90,100,1,0);
	ENTITY* enemies[MAX_ENTITYS] = {NULL};
	BULLET* bulletlist[MAX_BULLETS] = {NULL};
	if(addEnemy(enemies,bot1)){
		printf("couldnt add enemy");
		return 1;
	}
	
/*
	SDL_Color red = {255,0,0,255};	
	SDL_Color green = {0,255,0,255};	
	SDL_Color blue = {0,0,255,255};	
*/	
	
	while( !quit ){
		
	SDL_RenderClear(rend);
		while(SDL_PollEvent(&e)){
			switch(e.type){
				case SDL_QUIT:
					quit = 1;
					break;
				
				case SDL_KEYDOWN:
					switch(e.key.keysym.scancode){
						case SDL_SCANCODE_W:
							player->dir[1] = -10;
							break;
						case SDL_SCANCODE_S:
							player->dir[1] = 10;
							break;
						case SDL_SCANCODE_A:
							player->dir[0] = -10;
							break;
						case SDL_SCANCODE_D:
							player->dir[0] = 10;
							break;
						case SDL_SCANCODE_SPACE:
							break;
						default:
							break;
					}
					break;

				case SDL_KEYUP:
					switch(e.key.keysym.scancode){
						case SDL_SCANCODE_W:
							player->dir[1] = 0;
							break;
						case SDL_SCANCODE_S:
							player->dir[1] = 0;
							break;
						case SDL_SCANCODE_A:
							player->dir[0] = 0;
							break;
						case SDL_SCANCODE_D:
							player->dir[0] = 0;
							break;
						default:
							break;
					}
					break;
			}
		}
	updatePositions(player,enemies,bulletlist);
	renderEntities(rend,enemies,player);
	SDL_RenderPresent(rend);
	SDL_Delay(1000/60);
	}

	SDL_Quit();
	return 0;
}
