#include "../include/player.h"




Player::Player(std::string username, const char *filePath, SDL_Renderer *rndrr)
    :usrnm(username)
{
    renderer = rndrr;
    texture = loadIMG(filePath, renderer);
    frame = 0;
    ChangeWSrc(0, 0, 64, 64);
    ChangeWDst(0, 0, 128, 128);
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

    if(ctr < loops){
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
        if(frame == AnimationFrames && ctr == loops){
            frame = 1;
        }
    }


    //Descending or ascending
    if(num == 1){
        float testDescending = loops - (CtrForChange * frame);
        float testAscending = CtrForChange * frame;
        if(frame == AnimationFrames && ctr == loops){
            state = true;
        }
        else if(state){
            if(ctr == loops){
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
    std::cout<<frame<<"\n";
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