#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "../include/player.h"




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
    if(ctr < 22){
        ctr++;
    }
    else{
        ctr = 0;
    }
    if(0 < ctr && ctr < 5) frame = 0;
    if(5 < ctr && ctr < 10) frame = 1;
    if(10 < ctr && ctr < 15) frame = 2;
    if(15 < ctr && ctr < 20) frame = 3;
    return 1;

}
int Player::UserRender(){
    int change = frame * 64;
    ChangeSrc("x", change);
    Render();
    return 1;
}