#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "button.h"
#include "entity.h"
#include "mouse.h"

class Button : public Entity{
public:
    Button(SDL_Rect *buttonPos, const char *filePath, SDL_Renderer* rendrr, const Uint8 *pressed, SDL_Scancode key, SDL_Event *event);
    int AddMouse(Mouse *M);
    bool Pressed(SDL_Rect *rectC, bool change);
    bool ModifyCooldown (int cooldown);


private:
    inline static Uint64 timeout = 0;
    const Uint8 *state;
    SDL_Scancode activationKey;
    SDL_Event *E;
    Mouse *GlobalMouse;
    int Cooldown = 200;
};