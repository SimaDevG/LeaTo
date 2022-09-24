#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "../../include/Game/entity.h"
#include "../../include/Player/player.h"
#include "../../include/Game/func.h"

Player::Player(std::string username, const char *filePath, SDL_Renderer *rndrr)
    :usrnm(username)
{
    renderer = rndrr;
    texture = loadIMG(filePath, renderer);
}
int Player::MoveX(int xchange){
    ChangeDstX(ReturnDst()->x + xchange);
    return 1;
}
int Player::MoveY(int ychange){
    ChangeDstY(ReturnDst()->y + ychange);
    return 1;
}
int NxtFrame(){
    return 1;
}