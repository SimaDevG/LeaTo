#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>


#include "../include/event.h"
#include "../include/mouse.h"
#include "../include/entity.h"




Event::Event(SDL_Renderer *renderer, SDL_Rect SiPl, std::vector <Entity*> entities)
{
    for(Entity* e: entities){
        entities.push_back(e);
    }
}

void Event::AddMouse(Mouse* M){
    M = M;
}

void Event::AddEntity(Entity *entity){
    entities.push_back(entity);
}

void Event::Show(){
    for(Entity* e: entities){
        SDL_RenderCopy(renderer, e->ReturnTex(), e->ReturnSrc(), e->ReturnDst());
    }
}

void Event::RenderLoop(){
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Event::Window(int num){
    switch(num){
        case 1:
            Entity Window("../res/bg.png", renderer);
            Window.Render();
            Entity Exit("../res/exit.png", renderer);
            
    }
}