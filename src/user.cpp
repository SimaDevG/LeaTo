#include "../include/user.h"




User::User(std::string username, const char *filePath, SDL_Renderer *rndrr, SDL_Rect wSize)
    :usrnm(username), Window(wSize)
{
    renderer = rndrr;
    texture = loadIMG(filePath, renderer);
    frame = 0;
    ChangeWSrc(0, 0, 64, 64);
    ChangeWDst(40, 40, 128, 128);
}

//Move User
int User::MoveX(int xchange){
    if(xchange > 0 && ReturnDst()->x < (Window.w - ReturnDst()->w)){ //Positive asked change 
        ChangeDstX(ReturnDst()->x + xchange);                        //If position is less than window - user width -> Move
    }

    else if(xchange < 0 && 0 < ReturnDst()->x){         //Negative asked change
        ChangeDstX(ReturnDst()->x + xchange);           //If position is more than 0 (Width) -> Move
    }

    else{
        std::cout<<"Not valid input \n";
    }

    return 0;
}
int User::MoveY(int ychange){
    if(ychange > 0){
        if(ReturnDst()->y < (Window.h - ReturnDst()->h) -64){   //Positive asked change 
            ChangeDstY(ReturnDst()->y + ychange);           //If position is less than window - user height - hotbar height -> Move
        }
    }
    else if(ychange < 0){
        if(0 < ReturnDst()->y / 2){                         //Negative asked change
            ChangeDstY(ReturnDst()->y + ychange);           //If position is more than 0 (Height) -> Move
        }
    }
    else{
        std::cout<<"Not valid input \n";
    }

    return 0;
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
    change = (frame - 1) * PixelWidth;
    ChangeSrc("x", change);
    Render();
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