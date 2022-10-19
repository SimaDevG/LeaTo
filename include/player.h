#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>


#include "entity.h"
#include "mouse.h"

class Player : public Entity{
public:
    Player(std::string username, const char *filePath, SDL_Renderer *rndrr);
    int MoveX(int x);
    int MoveY(int y);
    int NxtFrame();
    int UserRender();
private:
    std::string usrnm;
    int frame;
    int ctr;
};