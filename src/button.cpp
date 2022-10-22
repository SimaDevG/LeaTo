#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "../include/block.h"
#include "../include/button.h"
#include "../include/entity.h"
#include "../include/event.h"
#include "../include/func.h"
#include "../include/mouse.h"
#include "../include/player.h"




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

bool Button::Pressed(SDL_Rect *rect, bool change){
    if(state[activationKey]){
        if(SDL_GetTicks64() >= timeout){
            change = !change;
            timeout = SDL_GetTicks64() + 100;
        }
    }
    return change;
}