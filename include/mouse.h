#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "entity.h"


class Mouse : public Entity{
public:
    Mouse(const char* filePath, SDL_Renderer *rendererm);
    void Update();
    SDL_Rect* GetPos();
    bool CheckPos(int x, int y);
private:
    SDL_Rect pos;
};