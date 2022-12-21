#include "../include/user.h"




User::User(std::string username, const char *filePath, SDL_Renderer *rndrr)
    :usrnm(username)
{
    renderer = rndrr;
    texture = loadIMG(filePath, renderer);
    frame = 0;
    ChangeWSrc(0, 0, 64, 64);
    ChangeWDst(0, 0, 128, 128);
}

//Move User
int User::MoveX(int xchange){
    ChangeDstX(ReturnDst()->x + xchange);
    return 1;
}
int User::MoveY(int ychange){
    ChangeDstY(ReturnDst()->y + ychange);
    return 1;
}


//Change User Frame & Render User
int User::UserRender(int num){
    int change;
    CtrForChange = loops / AnimationFrames;

    //Ctr Increase
    if(ctr < loops){
        ctr++;
    }
    else if(ctr == loops){
        ctr = 1;
    }

    //One Dir (Back)
    if(num == 0){
        int test = CtrForChange * frame;
        if(test < ctr && frame != AnimationFrames){
        frame++;
        }
        if(frame == AnimationFrames && loops == ctr){
            frame = 1;
        }
    }

    //(Both)Descending or ascending
    /**/
    if(num == 1){
        int testDescending = loops - (CtrForChange * frame); 
        int testAscending = CtrForChange * frame;

        //Ascending
        if(frame == AnimationFrames && loops == ctr){ //If ascending end, descend
            state = true;
            frame = AnimationFrames - 1;
        }

        else if(!state){
            if(testAscending < ctr &&  frame != AnimationFrames){
                frame++;                                                    
            }   
        }

        //Descending
        else if(state){
            if(ctr == loops){
                state = false;   //Back to default (Ascending)
            }
            else if(testDescending == ctr){   
                frame--;                            //Go down one frame (desc.)
            }
        }


    }
    //std::cout<<frame;
    if(frame == 0) frame = 1;
    Render();
    change = (frame - 1) * PixelWidth;
    ChangeSrc("x", change);
    return 1;
    //Same as in class "Block"
}

void User::ModifyAnimationFrames(int num){
    AnimationFrames = num;
}
void User::ModifyLoops(int num){
    loops = num;
}

void User::ModifyPixelW(int num){
    PixelWidth = num;
}