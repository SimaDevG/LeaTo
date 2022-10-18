#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "../include/block.h"
#include "../include/button.h"
#include "../include/entity.h"
#include "../include/event.h"
#include "../include/func.h"
#include "../include/player.h"


class Mouse : public Entity{
public:
    Mouse(const char* filePath, SDL_Renderer *rendererm);
    void Update();
    SDL_Rect* GetPos();
    bool CheckPos(int x, int y);
private:
    SDL_Rect pos;
};