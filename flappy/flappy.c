#include<SDL2/SDL.h> 
#include<SDL2/SDL_image.h> 
#include<SDL2/SDL_ttf.h>
#include<time.h>
typedef struct bird{
	SDL_Rect box;
	float velocity;
}BIRD;

typedef struct pipes{
	SDL_Rect boxes[4];
	struct pipes* next;
}PIPES;

const int scrollspeed = 2;
BIRD* brd;
int gw;
int gh;
int score = 0;
SDL_bool collision(PIPES* p){
	if(brd->box.y+brd->box.h >= gh || brd->box.y <= 0){
		return SDL_TRUE;
	}
	
	for(PIPES* pipes = p; pipes != NULL; pipes = pipes->next){
		for(int i = 0; i < 4; i++){
			if(SDL_HasIntersection(&brd->box, &pipes->boxes[i])){
				return SDL_TRUE;
			}
		}
	}
	return SDL_FALSE;
}

PIPES* createpipe(){
		int gap = rand() % (gh-400+1) +200;
		PIPES* n = (PIPES*)malloc(sizeof(PIPES));
		n->boxes[0] = (SDL_Rect){gw,0,100,gap-75};
		n->boxes[1] = (SDL_Rect){gw,gap+100,100,gh};
		n->boxes[2] = (SDL_Rect){gw-25,gap-75,150,50};
		n->boxes[3] = (SDL_Rect){gw-25,gap+100,150,50};
		n->next = NULL;
		return n;
}

PIPES* lastpipe(PIPES* p){
	if(p->next != NULL){
		return lastpipe(p->next);
	}
	else{
		return p;
	}
	
}

void move(float speed){
	brd->box.y -= (int)speed;
}

int main(){
	srand(time(NULL));
	if(SDL_Init(SDL_INIT_VIDEO)!= 0){
		printf("error initializing video\n");
		SDL_Quit();
		return 1;
	}
	TTF_Init();
	SDL_Window* win = SDL_CreateWindow("FLAPPY",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,600,800,0);
	if(win == NULL){
		printf("error creating window\n");
		TTF_Quit();
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
	TTF_Font* font = TTF_OpenFont("/usr/share/fonts/noto/NotoSans-Regular.ttf", 25);
	SDL_Color color = {255,255,255};
	char scr[50];
	sprintf(scr, "%d", score);
	int scw,sch;
	SDL_Surface* scsur;
	SDL_Texture* sctex;
	SDL_Rect screct = {gw-50,gh-50,scw,sch};
	
	SDL_Surface* ps = IMG_Load("pipe.png");
	if(!ps){
		printf("error creating surfaces\n");
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(rend);
		TTF_Quit();
		SDL_Quit();
		return 1;
	}
	
	SDL_Texture* ptx = SDL_CreateTextureFromSurface(rend, ps);
	if(!ptx){
		printf("error creating textures\n");
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(rend);
		TTF_Quit();
		SDL_Quit();
		return 1;
		
	}
	
	SDL_FreeSurface(ps);
	SDL_GetWindowSize(win, &gw, &gh);
	SDL_RenderClear(rend);
	PIPES* n = createpipe();
	SDL_RenderPresent(rend);
	brd = (BIRD*)malloc(sizeof(BIRD));	
	brd->box.x = 100;
	brd->box.y = gh/2;
	brd->box.w = 40;
	brd->box.h = 40;
	brd->velocity=-1;
	SDL_Event e;
	int quit = 0;
	while(!quit && !collision(n)){
		SDL_GetWindowSize(win, &gw, &gh);
		SDL_SetRenderDrawColor(rend,0,0,0,255);
		SDL_RenderClear(rend);
		sprintf(scr, "%d", score);
		scsur = TTF_RenderText_Solid(font,scr,color);
		sctex = SDL_CreateTextureFromSurface(rend,scsur);
		SDL_QueryTexture(sctex,NULL,NULL,&scw,&sch);
		screct.x = gw-50;
		screct.y = gh-50;
		screct.w = scw;
		screct.h = sch;
		SDL_RenderCopy(rend,sctex,NULL,&screct);
		move(brd->velocity);
		while(SDL_PollEvent(&e)){
			switch(e.type){
				case SDL_QUIT:
					quit=1;
					break;
				case SDL_KEYDOWN:
					switch(e.key.keysym.scancode){
						case SDL_SCANCODE_SPACE:
							brd->velocity=1;
							for(int i = 0; i < 5; i++){
								brd->velocity *= 2;
								move(brd->velocity);
							}
							brd->velocity=-1;
							break;
						
					}
				
			}	
		}
		
		SDL_SetRenderDrawColor(rend,255,0,0,255);
		SDL_RenderFillRect(rend,&brd->box);
		for(PIPES* p = n; p != NULL; p = p->next){
			for(int i = 0; i < 4; i++){
				p->boxes[i].x -= scrollspeed;
			}
		}
		
		if(n == NULL){
			printf("test");
		}
		if(lastpipe(n)->boxes[0].x == brd->box.x+50){
			PIPES* ne = createpipe();
			lastpipe(n)->next = ne;
		}
		if(n->boxes[3].x+n->boxes[3].w == brd->box.x-1){
			score++;
		}

		if(n->boxes[3].x+n->boxes[3].w < 0 && n->next != NULL){
			PIPES* temp = n->next;
			free(n);
			n = temp;
		}

		SDL_SetRenderDrawColor(rend,0,255,0,255);
		for(PIPES* x = n; x != NULL; x = x->next){
			for(int i = 0; i < 4; i++){
				SDL_RenderCopy(rend,ptx,NULL,&x->boxes[i]);
			}
		}
		brd->velocity *= 1.075;
		SDL_RenderPresent(rend);
		SDL_Delay(1000/60);
	}
	printf("score: %d\n", score);	
	return 0;
}
