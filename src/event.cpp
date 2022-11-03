#include "../include/event.h"









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
    for(Button* b : buttons){
        if((SDL_RenderCopy(b->ReturnRenderer(), b->ReturnTex(), b->ReturnSrc(), b->ReturnDst())!= 0)){
            std::cout<<"SDL didn't render out at Event::Show. SDL_Error: "<< SDL_GetError();
        }
    }
    return 1;
}

void Event::AddButton(Button *buttonAdd){
    buttons.push_back(buttonAdd);
}

void Event::AddButtonV(std::vector <Button*> buttonVector){
    for(Button *beAddedButtons : buttonVector){
        buttons.push_back(beAddedButtons);
    }
}
