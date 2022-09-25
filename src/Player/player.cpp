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
    frame = 0;
}
int Player::MoveX(int xchange){
    ChangeDstX(ReturnDst()->x + xchange);
    return 1;
}
int Player::MoveY(int ychange){
    ChangeDstY(ReturnDst()->y + ychange);
    return 1;
}
int Player::NxtFrame(){
    if(ctr < 880){
        ctr++;
    }
    else{
        ctr = 0;
    }
    if(0 < ctr && ctr < 200) frame = 0;
    if(200 < ctr && ctr < 400) frame = 1;
    if(400 < ctr && ctr < 600) frame = 2;
    if(600 < ctr && ctr < 800) frame = 3;
    return 1;

}
int Player::UserRender(){
    int change = frame * 64;
    ChangeSrc("x", change);
    Render();
    return 1;
}