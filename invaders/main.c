#include "inv.h"

int main(void){

	if(SDL_Init(SDL_INIT_VIDEO)!= 0){
		printf("error initializing video\n");
		SDL_Quit();
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow("Invaders",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1600,900,0);
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
	SDL_Delay(5000);
	SDL_Quit();
	return 0;
}
