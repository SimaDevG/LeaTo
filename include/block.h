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
    int UseBlock(Player *User);

private:
    SDL_Texture *tex;
    Button* BlockButton;

    Event* UseMenu;
    bool MenuinUse = false;
    int ctr = 0;
    int frame = 0;

};

void RenderVectorBlocks(std::vector<Block*> blk);