#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>


#include "entity.h"

class Player : public Entity{
public:
    Player(std::string username, const char *filePath, SDL_Renderer *rndrr);
    int MoveX(int x);
    int MoveY(int y);
    int NxtFrame(int num);
    int PlayerRender();
    void ModifyAnimationFrames(int num);
    void ModifyLoops(int num);
    void ModifyPixelW(int num);

private:
    std::string usrnm;

    //Animation
    int frame;
    int ctr;
    float CtrForChange;
    int AnimationFrames = 4;
    int PixelWidth = 64;
    float loops = 100;
    bool state = false;
};