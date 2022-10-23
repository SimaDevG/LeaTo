#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>


#include "block.h"
#include "button.h"
#include "entity.h"
#include "event.h"
#include "mouse.h"
#include "player.h"


class Block : public Entity{
public:
    Block(const char *filePath, SDL_Renderer *rendrr, Button *Btn, Event* UseMn);
    int BlockAnimation();
    int AddAnimationFrames(int num);
    int UseBlock(Player *User);

    int AddBlockNumber(int num);
    int ReturnBlockNumber();
    
    Button* ReturnBlockButton();

    Event* ReturnBlockEvent();

private:
    SDL_Texture *tex;

    Button* BlockButton;

    Event* UseMenu;

    bool MenuinUse = false;
    int ctr = 0;
    int frame = 1;
    int BlockNumber;

    int AnimationFrames;
    int CtrForChange;

};

void RenderVectorBlocks(std::vector<Block*> blk);