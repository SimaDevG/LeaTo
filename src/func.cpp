#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "../include/block.h"
#include "../include/button.h"
#include "../include/entity.h"
#include "../include/event.h"
#include "../include/func.h"
#include "../include/mouse.h"
#include "../include/player.h"



SDL_Texture* loadIMG(const char* filepath, SDL_Renderer* renderer){
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filepath);
	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void init(SDL_Window *window, SDL_Renderer *renderer){
    // Initialize SDL2
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout<<"Something didn't go right. Error: "<<SDL_GetError()<<"/n";
    } 
    if(!(IMG_Init(IMG_INIT_PNG))){
        std::cout<<"SDL_image couldn't initialize";
    }
    if(window == NULL){
        std::cout<<"Window is NULL: "<<SDL_GetError();
    }
    //Create a renderer
    if(renderer == NULL){
        std::cout<<"Renderer is NULL: "<<SDL_GetError();
    }

}

bool checkCollision(SDL_Rect *rect1, SDL_Rect *rect2){
    if(SDL_HasIntersection(rect1, rect2)){
        return 1;
    }
    else{
        return 0;
    }
}