#include<time.h>
#include "snake.c"
int get50(int rand);
int main() 
{ 
	//char* sc;
    // returns zero on success else non-zero 
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {			//init SDL 
        printf("error initializing SDL: %s\n", SDL_GetError()); 
	SDL_Quit();
	return 1;
    } 
    SDL_Window* win = SDL_CreateWindow("SNAKE",				//init Window 
                                       SDL_WINDOWPOS_CENTERED, 
                                       SDL_WINDOWPOS_CENTERED, 
                                       800, 600, 0); 
    if (win == NULL) {
	printf("error");
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 1;
   }
	SDL_GetWindowSize(win,&maxw,&maxh);
	srand(time(NULL)); //initializing random seed every second
	SNAKE *sn = (SNAKE*)malloc(sizeof(SNAKE)); //declaring snake
	sn->hitbox.x = get50(rand() % maxw); //random position of snake at first
	sn->hitbox.y = get50(rand() % maxh);
	sn->dir[0] = 0;
	sn->dir[1] = 0;
	sn->next = NULL;
	foodhitbox.x = get50(rand() % maxw);//random food pos
	foodhitbox.y = get50(rand() % maxh);

	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC; //init renderer
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
	if(!rend){
		printf("error with renderer");
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}
	
	    SDL_Surface *snak = IMG_Load("snake.png"); //load pictures to surfaces 
	    SDL_Surface *f = IMG_Load("food.png"); 
	if(!snak && !f){
		printf("error with creating surfaces");
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(rend);
		SDL_Quit();
		return 1;
	}
	//SDL_Color green = {0,255,0};
	//TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
	//sprintf(sc, "%d", score);
	//SDL_Surface* scoretext = TTF_RenderText_Solid(Sans, sc, green);
	//SDL_Texture* scoretex = SDL_CreateTextureFromSurface(rend, scoretext); 
	//SDL_FreeSurface(scoretext);
	//SDL_Rect scorebox = (SDL_Rect){.x = maxw, .y = maxh};
	//SDL_QueryTexture(scoretex, NULL, NULL, &scorebox.w, &scorebox.h);


	    SDL_Texture* stex = SDL_CreateTextureFromSurface(rend, snak); //make textures
	    SDL_Texture* ftex = SDL_CreateTextureFromSurface(rend, f);
	if(!stex && !ftex){
		printf("error with creating textures");
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(rend);
		SDL_Quit();
		return 1;
	}
	    SDL_FreeSurface(snak); 			//surfaces not needed anymore: free them
	    SDL_FreeSurface(f);
            //Update the surface
		//SDL_SetRenderDrawColor(rend,255,255,255,255);
		SDL_RenderClear(rend);	
		SDL_RenderPresent(rend);//show first frame

		SDL_QueryTexture(stex, NULL, NULL, &sn->hitbox.w, &sn->hitbox.h);
		SDL_QueryTexture(ftex, NULL, NULL, &foodhitbox.w, &foodhitbox.h);
		
   SDL_Event e;				//event to capture input like keyboard
   int quit = 0;
   while(!quit && !collision(sn, sn->next)){//main loop 
		SDL_RenderClear(rend);
	   while(SDL_PollEvent(&e)){//event handling
		switch(e.type){
			case SDL_QUIT:
				quit = 1;
				break;

			case SDL_KEYDOWN:
				switch (e.key.keysym.scancode){//key handling
					case SDL_SCANCODE_W:
					case SDL_SCANCODE_UP:
						sn->dir[1] = -50;
						sn->dir[0] = 0;
						break;
					case SDL_SCANCODE_S:
					case SDL_SCANCODE_DOWN:
						sn->dir[1] = 50;
						sn->dir[0] = 0;
						break;
					case SDL_SCANCODE_A:
					case SDL_SCANCODE_LEFT:
						sn->dir[0] = -50;
						sn->dir[1] = 0;
						break;
					case SDL_SCANCODE_D:
					case SDL_SCANCODE_RIGHT:
						sn->dir[0] = 50;
						sn->dir[1] = 0;
						break;
				}
		} 

	   }
	SDL_GetWindowSize(win,&maxw,&maxh);//writes window width and height to previously declared global vars
	maxw = get50(maxw);
	maxh = get50(maxh);
	move(sn);//move according to global vars width and height
	placefood(grow(sn));
	for(SNAKE* s = sn; s != NULL; s = s->next){
		SDL_RenderCopy(rend,stex,NULL,&s->hitbox);
	}
	SDL_QueryTexture(stex, NULL, NULL, &last(sn)->hitbox.w, &last(sn)->hitbox.h);
	//sprintf(sc, "%d", score);
	//SDL_QueryTexture(scoretex, NULL, NULL, &scorebox.w, &scorebox.h);
	//SDL_RenderCopy(rend, scoretex, NULL, &scorebox);
	SDL_RenderCopy(rend, ftex, NULL, &foodhitbox);
	SDL_RenderPresent(rend);
	SDL_Delay(8000/144);
   }
	if(collision(sn, sn->next)){
		printf("GAME OVER\n");
		printf("Score :%d\n", length(sn));
	}
   freesnake(sn);
   SDL_DestroyWindow(win);
   SDL_DestroyRenderer(rend);
   SDL_DestroyTexture(stex);
   SDL_DestroyTexture(ftex);
   SDL_Quit();
   return 0;
} 

int get50(int rand){
	int rest = rand % 50;
	return rand - rest;
}
