#include "../include/utility.h"
/*
File for all menu related stuff
*/


/*Mouse*/
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

/*Button*/
Button::Button(SDL_Rect *buttonPos, SDL_Renderer* rendrr, const Uint8 *pressed, SDL_Scancode key)
    :state(pressed), activationKey(key){
    mouseState = NULL;
    renderer = rendrr;
    dst = buttonPos;
}

int Button::AddEvent(SDL_Event* Event){
    event = Event;
    return 0;
}

int Button::AddMouse(Mouse *M, bool *mouse = nullptr){
    GlobalMouse = M;
    mouseState = mouse;
    return 0;
}

int Button::AddFunction(void func()){
    function = func;
    return 0;
}

int Button::AddGButton(const char *filePath){
    texture = loadIMG(filePath, renderer);
    return 0;
}

bool Button::PressedK(){
    if(state[activationKey]){
        if(SDL_GetTicks64() >= timeout){
            timeout = SDL_GetTicks64() + Cooldown;
            function();
        }
    }
    return 0;
}

bool Button::PressedM(SDL_Rect &rect){
    if(*mouseState && CheckCollision(GlobalMouse) && SDL_GetTicks64() >= timeout){
        function();
        timeout = SDL_GetTicks64() + Cooldown;
    }
    return true;
}

bool Button::ModifyCooldown(int cooldown){
    Cooldown = cooldown;
    return true;
}

void Button::AddEvent(Event* EventToAdd){
    EventAdd = EventToAdd;
}


/*Event*/
Event::Event()
{
}
Event::Event(SDL_Renderer *renderer, std::vector<Entity *> entities)
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
    return 0;
}

void Event::AddButton(Button *buttonAdd){
    buttons.push_back(buttonAdd);
}

void Event::AddButtonV(std::vector <Button*> buttonVector){
    for(Button *beAddedButtons : buttonVector){
        buttons.push_back(beAddedButtons);
    }
}





Hotbar::Hotbar(SDL_Renderer *Renderer){
    renderer = Renderer;
    ReturnEntities().push_back(new Entity("../res/hotbarbox.png", renderer));
}

int Hotbar::RenderHotbar(){                                             //Renders entire hotbar, changing src and therefore -> focus effect
    int iterator = 0;
    for(bool *box : inUse){
        if(*box){
            entities[iterator]->ChangeWSrc(64, 0, 64, 64);
        }
        else{
            entities[iterator]->ChangeWSrc(0, 0, 64, 64);
        }

        // std::cout<<*inUse[iterator]<<std::endl;
        iterator++;
    }
    Show();
    return 0;
}

std::vector <bool*> Hotbar::ReturninUse(){ //Returns Vector of the Hotbar Block in Use
    return inUse;
}

int Hotbar::setinUse(int index, bool value){    //Unfocuses All Other Hotbar Components, And Focuses The Inquired One
    for(bool *box : inUse){
        *box = false;
    }
    *inUse[index] = value;
    std::cout<<*inUse[index]<<std::endl;
    return 0;
}