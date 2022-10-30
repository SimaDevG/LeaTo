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
int Player::NxtFrame(int num){
    int change;
    CtrForChange = loops / AnimationFrames;
    int max = CtrForChange * AnimationFrames;

    if(ctr < max){
        ctr++;
    }
    else{
        ctr = 0;
    }
    if(num == 0){
        int test = CtrForChange * frame;
        if(test < ctr){
        frame++;
        }
        if(frame == AnimationFrames && ctr == max){
            frame = 1;
        }
    }


    //Descending or ascending
    if(num == 1){
        int testDescending = 100 - (CtrForChange * frame);
        int testAscending = CtrForChange * frame;
        if(frame == AnimationFrames && ctr == max){
            state = true;
        }
        else if(state){
            if(ctr == max){
                state = false;
            }
            else if(testDescending < ctr){
                frame--;
            }
        }
        else if(!state){
            if(testAscending < ctr){
                frame++;
            }   
        }
    }
    if(frame == 0) frame = 1;
    change = (frame - 1) * PixelWidth;
    ChangeSrc("x", change);
    Render();
    return 1;
}
int Player::PlayerRender(){
    int change = frame * 64;
    ChangeSrc("x", change);
    Render();
    return 1;
}

void Player::ModifyAnimationFrames(int num){
    AnimationFrames = num;
}
void Player::ModifyLoops(int num){
    loops = num;
}

void Player::ModifyPixelW(int num){
    PixelWidth = num;
}