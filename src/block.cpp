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


        if(frame == AnimationFrames && loops == ctr){ //If ascending end, descend
            state = true;
        }

        //Ascending
        else if(!state){
            if(testAscending < ctr &&  frame != AnimationFrames){
                frame++;                                                    
            }   
        }


        if(state){
            if(ctr == loops){
                state = false;   //Back to default (Ascending)
            }
            else if(testDescending == ctr){   
                frame--;                            //Go down one frame (desc.)
            }
        }



    }
    if(frame == 0) frame = 1;
    change = (frame - 1) * PixelWidth;
    std::cout<<ctr<<" "<<frame<<" "<<CtrForChange<<"\n";
    ChangeSrc("x", change);
    Render();
    return 1;

}

int Block::AddAnimationFrames(int num){
    AnimationFrames = num;
    return 1;
}

int Block::UseBlock(User *user){
    if(checkCollision(user->ReturnDst(), ReturnDst())){
        BlockButton->Render();
        MenuinUse = BlockButton->Pressed(ReturnDst(), MenuinUse);
        if(MenuinUse){
            UseMenu->Show();
        }
    }
    else{
        MenuinUse = false;
    }
    return 1;
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
void RenderVectorBlocks(std::vector<Block*> blk){
    for(Block * b : blk){
        b->Render();
    }
}
