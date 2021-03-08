#include "inv.h"
#include<time.h>

int main(void){

	if(SDL_Init(SDL_INIT_VIDEO)!= 0){
		printf("error initializing video\n");
		SDL_Quit();
		return 1;
	}

	SDL_Window* win = SDL_CreateWindow("Invaders",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,960,540,0);
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
	
	while( !quit ){
		
		while(SDL_PollEvent(&e)){
			switch(e.type){
				case SDL_QUIT:
					quit = 1;
					break;
				
				case SDL_KEYDOWN:
					switch(e.key.keysym.scancode){
						case SDL_SCANCODE_W:
							break;
						case SDL_SCANCODE_S:
							break;
						case SDL_SCANCODE_A:
							break;
						case SDL_SCANCODE_D:
							break;
						default:
							break;
					}
			}
		}
		
	}
	


	SDL_Delay(5000);
	SDL_Quit();
	return 0;
}
