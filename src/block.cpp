#include "../include/block.h"





Block::Block(const char *filePath, SDL_Renderer *rendrr, Button *Btn, Event *UseMn)
    :BlockButton(Btn), UseMenu(UseMn)
{
    texture = loadIMG(filePath, rendrr);
    renderer = rendrr;
}

int Block::BlockAnimation(int num){
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
    if(frame == 0) frame = 1;
    Render();
    change = (frame - 1) * PixelWidth;
    ChangeSrc("x", change);
    return 1;
    //Same as in class "User"
}

int Block::AddAnimationFrames(int num){
    AnimationFrames = num;
    return 1;
}

int Block::UseBlock(User *user){
    if(checkCollision(user->ReturnDst(), ReturnDst())){
        BlockButton->Pressed(ReturnDst());
    }
        return 0;
}

int Block::AddBlockNumber(int num){
    BlockNumber = num;
    return 1;
}

int Block::ReturnBlockNumber(){
    return BlockNumber;
}

void Block::ModifyLoops(int num){
    loops = num;
}

Button* Block::ReturnBlockButton(){
    return BlockButton;
}

Event* Block::ReturnBlockEvent(){
    return UseMenu;
}

int Block::PixelWidthBl(int num){
    PixelWidth = num;
    return 1;
}


//Renders a vector of blocks, not a part of class "Block"
void RenderVectorBlocks(std::vector<Block*> blk){
    for(Block * b : blk){
        b->Render();
    }
}
