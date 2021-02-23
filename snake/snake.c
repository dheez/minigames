#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
int get50(int rand);
typedef struct snake{		//struct of the snake (position, direction, pointer to next)
	SDL_Rect hitbox;
	int oldpos[2];
	int dir[2];
	struct snake *next;
}SNAKE;
	SDL_Rect foodhitbox;

int maxh;//int for storing the window sizes
int maxw;

void upddir(SNAKE* sn){
	if(sn->next != NULL){
		sn->next->dir[0] = sn->hitbox.x-sn->next->hitbox.x;
		sn->next->dir[1] = sn->hitbox.y-sn->next->hitbox.y;
		upddir(sn->next);
	}
}

void move(SNAKE* sn){          //function that moves the snake (dumb vector shit)
	sn->oldpos[0] = sn->hitbox.x;
	sn->oldpos[1] = sn->hitbox.y;
	sn->hitbox.x += sn->dir[0]; 
	sn->hitbox.y += sn->dir[1];
		if( sn->hitbox.x < 0){
			sn->hitbox.x = maxw-sn->hitbox.w;
		}
		if( sn->hitbox.x+sn->hitbox.w > maxw){
			sn->hitbox.x = 0;
		}
		if( sn->hitbox.y < 0){
			sn->hitbox.y = maxh-sn->hitbox.h;
		}
		if( sn->hitbox.y+sn->hitbox.h > maxh){
			sn->hitbox.y = 0;
		}
	if(sn->next != NULL){
		move(sn->next);
	}
	
}

int length(SNAKE *sn){
	if(sn->next != NULL){
		return 1 + length(sn->next);
	}
	else return 1;
}

SDL_bool collision(SNAKE *sn, SNAKE *n ){ //function which tests, if there is a collision with the snake
	upddir(sn);
	for(SNAKE* x = n; x != NULL; x = x -> next){
		if(SDL_HasIntersection(&sn->hitbox, &x->hitbox)){
			if(sn->dir[0]+x->dir[0] != 0 || sn->dir[1]+x->dir[1] != 0){
				return SDL_TRUE;	
			}
		}
	}	
	return SDL_FALSE;
}

SNAKE* last(SNAKE *sn){			//last struct of the snake
	if(sn->next == NULL){
		return sn;
	}	
	else return last(sn->next); 
}

int grow(SNAKE *sn){	//when snake eats the food, a new node is added to the back
	SDL_Rect hit = sn->hitbox;
	if (SDL_HasIntersection(&hit, &foodhitbox)){
		SNAKE* l = last(sn);
		SNAKE *tail = (SNAKE*)malloc(sizeof(SNAKE)); //important!! else segmentation fault.
		tail->hitbox.x = l->oldpos[0];
		tail->hitbox.y = l->oldpos[1];
		tail->dir[0] = l->hitbox.x-tail->hitbox.x; 
		tail->dir[1] = l->hitbox.y-tail->hitbox.y;
		tail->next = NULL;
		l->next = tail;
		return 1;
	}
	else return 0;
}

void placefood(int bool){	
	if(bool || maxw < foodhitbox.x || maxh < foodhitbox.y){
		foodhitbox.x = get50(rand() % maxw);
		foodhitbox.y = get50(rand() % maxh);
	}
	
}

void freesnake(SNAKE* sn){
	if(sn->next != NULL){
		SNAKE* n = sn->next;
		free(sn);
		freesnake(n);
	}
	else free(sn);	
}	
