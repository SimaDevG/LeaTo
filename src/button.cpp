#include "../include/button.h"




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

bool Button::Pressed(SDL_Rect *rect, bool change, bool showEvent = false){
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