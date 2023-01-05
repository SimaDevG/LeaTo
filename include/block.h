#pragma once
#include "utility.h"
class Block : public Entity{
public:
    Block(const char *filePath, SDL_Renderer *rendrr, Button *Btn, Event* UseMn);
    int BlockAnimation(int num);
    int AddAnimationFrames(int num);
    int UseBlock(User *user);

    int AddBlockNumber(int num);
    int ReturnBlockNumber();

    void ModifyLoops(int num);
    
    Button* ReturnBlockButton();

    Event* ReturnBlockEvent();

    int PixelWidthBl(int num);

private:
    SDL_Texture *tex;

    Button* BlockButton;

    Event* menu;
    int loops = 100;
    bool MenuinUse = false;
    int ctr = 0;
    int frame = 1;
    int BlockNumber;

    bool state = false;
    int AnimationFrames = 1;
    int CtrForChange;
    int PixelWidth = 128;

};

void RenderVectorBlocks(std::vector<Block*> blk);