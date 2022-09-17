#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "../include/entity.h"
#include "../include/func.h"
#include "../include/mouse.h"



//SDL Initializations
SDL_Surface *logo;

//Game variables
const Uint8 *state = SDL_GetKeyboardState(NULL);

//Loop variables
SDL_Event input;
bool* running = new bool(true);

//Resources
std::vector <Entity*> Entities;







void init(){
    // Initialize SDL2
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout<<"Something didn't go right. Error: "<<SDL_GetError()<<"/n";
    } 
    if(!(IMG_Init(IMG_INIT_PNG))){
        std::cout<<"SDL_image couldn't initialize";
    }

}



int main(int argc, char* argv[]) {
    //Create a window
    SDL_Window* window = SDL_CreateWindow( "LeaTo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1080, 720, SDL_WINDOW_RESIZABLE);
    if(window == NULL){
        std::cout<<"Window is NULL: "<<SDL_GetError();
    }
    //Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(window == NULL){
        std::cout<<"Renderer is NULL: "<<SDL_GetError();
    }

    logo = IMG_Load("../res/logo.png");
    SDL_SetWindowIcon(window, logo);
    init();

    Mouse cursor("../res/cursor.png", renderer);
    Entity Bg("../res/bg.png", renderer);

    while(*running){
        while(SDL_PollEvent(&input)){
            if(input.type == SDL_QUIT){
                *running = false;
            }
        }
        
        SDL_RenderClear(renderer);
        Bg.Render();
        cursor.Update();
        SDL_RenderPresent(renderer);
        std::cout<<SDL_GetError();

        
    }
    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}