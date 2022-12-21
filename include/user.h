#pragma once

#include "entity.h"

class User : public Entity{
public:
    User(std::string username, const char *filePath, SDL_Renderer *rndrr);
    int MoveX(int x);
    int MoveY(int y);
    int UserRender(int num);
    void ModifyAnimationFrames(int num);
    void ModifyLoops(int num);
    void ModifyPixelW(int num);
private:
    std::string usrnm;

    //Animation
    int frame = 1;
    int ctr = 0;
    int CtrForChange;
    int AnimationFrames = 4;
    int PixelWidth = 64;
    int loops = 100;
    bool state = false;
    
};