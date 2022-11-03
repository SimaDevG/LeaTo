#include "../include/block.h"






Block::Block(const char *filePath, SDL_Renderer *rendrr, Button *Btn, Event *UseMn)
    :BlockButton(Btn), UseMenu(UseMn)
{
    texture = loadIMG(filePath, rendrr);
    renderer = rendrr;
}

int Block::BlockAnimation(int num){
    int change;
    CtrForChange = 100 / AnimationFrames;
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

int Block::AddAnimationFrames(int num){
    AnimationFrames = num;
    return 1;
}

int Block::UseBlock(Player *User){
    if(checkCollision(User->ReturnDst(), ReturnDst())){
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
