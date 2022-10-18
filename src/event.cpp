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








Event::Event(SDL_Renderer *renderer, std::vector <Entity*> entities)
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



std::vector <Entity*> Event::ReturnEntities(){
    return entities;
}



Entity* Event::ReturnEntity(int num){
    return ReturnEntities()[num];
}

int Event::Show(){
    for(Entity* e: entities){
        if((SDL_RenderCopy(e->ReturnRenderer(), e->ReturnTex(), e->ReturnSrc(), e->ReturnDst())!= 0)){
            std::cout<<"SDL didn't render out at Event::Show. SDL_Error: "<< SDL_GetError();
        }
    }
    return 1;
}


