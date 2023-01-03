#include "../include/func.h"


//Loads an IMG (PNG)
SDL_Texture* loadIMG(const char* filepath, SDL_Renderer* renderer){
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filepath);
	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

//Initializing function (Window)
void init(SDL_Window *window, SDL_Renderer *renderer){
    // Initialize SDL2
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout<<"SDL couldn't initialize. Error: "<<SDL_GetError()<<"\n";
    } 
    //SDL_image
    if(!(IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG || IMG_INIT_WEBP))){                         //Supports JPG, PNG and WEBP format.
        std::cout<<"SDL_image couldn't initialize. Error: "<< SDL_GetError()<< "\n";
    }
    //SDL_TTF
    if(TTF_Init() != 0){
        std::cout<<"SDL_TTF couldn't initialize. Error: "<< TTF_GetError() << "\n"; /*Could use SDL_GetError() (Macro for it)*/
    }
    if(window == NULL){
        std::cout<<"Window is NULL: "<<SDL_GetError();
    }
    //Create a renderer
    if(renderer == NULL){
        std::cout<<"Renderer is NULL: "<<SDL_GetError();
    }

}

//Check collision between to SDL_Rect
bool checkCollision(SDL_Rect *rect1, SDL_Rect *rect2){
    if(SDL_HasIntersection(rect1, rect2) == SDL_TRUE){
        return 1;
    }
    else{
        return 0;
    }
}
