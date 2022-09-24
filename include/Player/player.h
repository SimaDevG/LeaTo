#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "../Game/entity.h"

class Player : public Entity{
public:
    Player(std::string username, const char *filePath, SDL_Renderer *rndrr);
    int MoveX(int x);
    int MoveY(int y);
    int NxtFrame();
private:
    std::string usrnm;
};