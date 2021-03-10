#include "inv.h"

int renderEntities(SDL_Renderer* rend, ENTITY** entities, ENTITY* player){
	SDL_SetRenderDrawColor(rend,255,0,0,255);
	SDL_RenderFillRect(rend,player->hb);
	SDL_SetRenderDrawColor(rend,255,0,255,255);
	for(int i = 0; i < MAX_ENTITYS; i++){
		if(entities[i] != NULL){
			SDL_RenderFillRect(rend,entities[i]->hb);
		}
		
	}
	SDL_SetRenderDrawColor(rend,0,0,0,255);
	return 0;
}
