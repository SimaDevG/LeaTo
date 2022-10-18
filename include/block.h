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
#include "../include/mouse.h"
#include "../include/player.h"


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

    int frame = 0;

};