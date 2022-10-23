#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>


#include "../include/block.h"
#include "../include/button.h"
#include "../include/entity.h"
#include "../include/event.h"
#include "../include/func.h"
#include "../include/mouse.h"
#include "../include/player.h"






Block::Block(const char *filePath, SDL_Renderer *rendrr, Button *Btn, Event *UseMn)
    :BlockButton(Btn), UseMenu(UseMn)
{
    texture = loadIMG(filePath, rendrr);
    renderer = rendrr;
}

int Block::BlockAnimation(){
    int change;
    CtrForChange = 100 / AnimationFrames;

    if(ctr < 100){
        ctr++;
    }
    else{
        ctr = 0;
    }
    int test = CtrForChange * frame;
    std::cout<<test<<"\n";
    if(test > ctr){
        frame++;
    }
    if(frame == AnimationFrames && ctr == 100){
        frame = 1;
    }
    std::cout<<"Counter = "<< ctr <<"   Frame = "<< frame << "\n";
    change = (frame - 1) * 128;
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

void RenderVectorBlocks(std::vector<Block*> blk){
    for(Block * b : blk){
        b->Render();
    }
}