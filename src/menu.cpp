#include "../include/menu.h"
// File for all classes related to menus.


//Mouse
Mouse::Mouse(const char* filePath, SDL_Renderer *rendererm)
{
    renderer = rendererm;
    texture = loadIMG(filePath, renderer);
    src->x = 0;
    src->y = 0;
    src->w = 64;
    src->h = 64;

    dst->x = 0;
    dst->y = 0;
    dst->w = 25;
    dst->h = 25;

    SDL_ShowCursor(false);
}

void Mouse::Update(){
    SDL_GetMouseState(&dst->x, &dst->y);
    SDL_RenderCopy(renderer, texture, src, dst);
}

SDL_Rect* Mouse::GetPos(){
    SDL_GetMouseState(&pos.x, &pos.y);
    return &pos;
} 

bool Mouse::CheckPos(int x, int y){
    SDL_GetMouseState(&pos.x, &pos.y);
    if(pos.x == x && pos.y == y){
        return true;
    }
    else{
        return false;
    }
}

//Button
Button::Button(SDL_Rect *buttonPos, const char *filePath, SDL_Renderer* rendrr, const Uint8 *pressed, SDL_Scancode key, SDL_Event *event)
    :state(pressed), activationKey(key), E(event)
{
    texture = loadIMG(filePath, rendrr);
    renderer = rendrr;
    dst = buttonPos;
}

int Button::AddMouse(Mouse *M){
    GlobalMouse = M;
    return 1;
}

bool Button::Pressed(SDL_Rect *rect, bool change, bool showEvent){
    if(state[activationKey]){
        if(SDL_GetTicks64() >= timeout){
            if(!showEvent){
                change = !change;
            }
            else if(EventAdd != nullptr){
                EventAdd->Show();
            }
            timeout = SDL_GetTicks64() + Cooldown;
        }
    }
    return change;
}

bool Button::ModifyCooldown(int cooldown){
    Cooldown = cooldown;
    return true;
}

void Button::AddEvent(Event* EventToAdd){
    EventAdd = EventToAdd;
}


//Event
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
