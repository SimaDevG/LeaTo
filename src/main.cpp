#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "../include/block.h"
#include "../include/button.h"
#include "../include/entity.h"
#include "../include/event.h"
#include "../include/func.h"
#include "../include/mouse.h"
#include "../include/player.h"


/*To Do
- Background
- Fix Main Menu Button
- Fix LearningPods focus mod
- Main Communication Table
- Looks
- Networking
Set so that if window size gets to a sudden point, it will go down even more, so that only the Player1 is seen with the learning pod, including the timer.

Learningpod timer for study sessions


*/



/*git remote -v to go to website repo*/


//SDL Initializations
int *WindowWidth =  new int(1775);
int *WindowHeight = new int (1000);
SDL_Surface *logo;
SDL_Window* window = SDL_CreateWindow( "LeaTo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, *WindowWidth, *WindowHeight, SDL_WINDOW_RESIZABLE);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
Uint64 start;
Uint64 end;
//LeaTo variables
const Uint8 *state = SDL_GetKeyboardState(NULL);
SDL_Event *input = new SDL_Event;
bool running = true;

//Player
Player *Player1 = new Player("Sima", "../res/owlSpr.png", renderer);

//Vectors
std::vector <Entity*> Entities;
std::vector <Entity*> Hotbar_Entities; //Hotbar (1, 2, 3, 4)

//Resources
Entity *UseIcon = new Entity("../res/UseIcon.png", renderer);
Mouse *cursor = new Mouse("../res/cursor.png", renderer);

//Background & Main Menu
Block *Background = new Block("../res/bg.png", renderer, new Button(new SDL_Rect {}, "../res/UseIcon.png", renderer, state, SDL_SCANCODE_ESCAPE, input), new Event(renderer, std::vector <Entity*> {}));

int GlobalInit(){

    init(window, renderer);
    SDL_SetWindowMinimumSize(window, 300, 364);
    SDL_SetWindowMaximumSize(window, 1775, 1000);
    //Window logo
    logo = IMG_Load("../res/logo.png");
    SDL_SetWindowIcon(window, logo);


    Background->AddAnimationFrames(1);
    Background->ReturnBlockEvent()->AddEntity(new Entity("../res/LPMenu.png", renderer));
    Background->ReturnBlockEvent()->ReturnEntity(0)->ChangeWDst(100, 100, 1575, 800);
    Background->ReturnBlockEvent()->AddButton(new Button(new SDL_Rect  {500, 500, 64, 64}, "../res/UseIcon.png", renderer, state, SDL_SCANCODE_ESCAPE, input));
    Background->ReturnBlockButton()->ModifyCooldown(150);
    return 1;
}



//Hotbar
Event *Hotbar = new Event(renderer, Hotbar_Entities);
int HotbarInit(){
    for(int box = 0; box < 3; box++){
        Hotbar->AddEntity(new Entity("../res/hotbarbox.png", renderer));
        Hotbar->ReturnEntity(box)->ChangeWSrc(0, 0, 64, 64);
        Hotbar->ReturnEntity(box)->ChangeWDst(444 + 64 * box, 756, 64, 64);
    }
    return 1;
}

//Learning Pods
std::vector <Block*> LearningPods;

int LearningPodInit(){
    int ButtonPosX;
    int MenuPosX;
    int BlockPos;
    for(int BlNr = 1; BlNr < 5 ; BlNr++){
        if(BlNr == 1) BlockPos = (*WindowWidth * 0.1);
        else BlockPos = (*WindowWidth * (0.12 * BlNr));
        ButtonPosX = BlockPos + 32;
        MenuPosX = BlockPos - 86;

        Button *tempButton = new Button(new SDL_Rect {ButtonPosX, 383, 64, 64}, "../res/UseIcon.png", renderer, state, SDL_SCANCODE_E, input);
        tempButton->AddMouse(cursor);

        Entity *tempMenuBG = new Entity("../res/LPMenu.png", renderer);   tempMenuBG->ChangeWDst(MenuPosX, 233, 300, 300);
        std::vector <Entity*> *tempMenuEntities = new std::vector <Entity*>;
        Event *tempMenu = new Event(renderer, *tempMenuEntities);
        tempMenu->AddEntity(tempMenuBG);

        Block *TempBlock = new Block("../res/LearningPod.png", renderer, tempButton, tempMenu);
        TempBlock->ChangeWDst(BlockPos, 333, 128, 128);
        TempBlock->AddBlockNumber(BlNr);
        TempBlock->ChangeWSrc(0, 0, 128, 128);
        TempBlock->AddAnimationFrames(8);

        LearningPods.push_back(TempBlock);
    }
    return 3;
}



int Input(){
    //Movement
    if(state[SDL_SCANCODE_D]){
        Player1->MoveX(3);
    }
    if(state[SDL_SCANCODE_A]){
        Player1->MoveX(-3);
    }
    if(state[SDL_SCANCODE_S]){
        Player1->MoveY(3);
    }
    if(state[SDL_SCANCODE_W]){
        Player1->MoveY(-3);
    }
    //Hotbar
    if(state[SDL_SCANCODE_1]){
        for(int box = 0; box < 3; ++box){
            Hotbar->ReturnEntity(box)->ChangeSrc("x", 0);
        }
        Hotbar->ReturnEntity(0)->ChangeSrc("x", 64);
    }
    if(state[SDL_SCANCODE_2]){
        for(int box = 0; box < 3; ++box){
            Hotbar->ReturnEntity(box)->ChangeSrc("x", 0);
        }
        Hotbar->ReturnEntity(1)->ChangeSrc("x", 64);
    }
    if(state[SDL_SCANCODE_3]){
        for(int box = 0; box < 3; ++box){
            Hotbar->ReturnEntity(box)->ChangeSrc("x", 0);
        }
        Hotbar->ReturnEntity(2)->ChangeSrc("x", 64);
    }

    return 1;

}

float ReturnFrameRate(){
    return (end - start) / (float)SDL_GetPerformanceFrequency();
}
int ProportionsUpdate(){
    int BlockUpdateX;
    int BlockUpdateY;
    int HotbarBoxCtr = 0;
    
    //Getting current window size
    SDL_GetWindowSize(window, WindowWidth, WindowHeight);

    //Proportions
    for(Block* Block : LearningPods){
        BlockUpdateX = (*WindowWidth * (0.12 * Block->ReturnBlockNumber()));
        BlockUpdateY = *WindowHeight * 0.3;

        Block->ChangeWDst(BlockUpdateX, BlockUpdateY, 128, 128);

        Block->ReturnBlockButton()->ChangeWDst(BlockUpdateX + 32, BlockUpdateY + 32, 64, 64);

        Block->ReturnBlockEvent()->ReturnEntities()[0]->ChangeWDst(BlockUpdateX - 86, BlockUpdateY - 100, 300, 300);

    }

    //Hotbar 
    for(Entity *HotbarBox : Hotbar->ReturnEntities()){
            HotbarBox->ChangeWDst((*WindowWidth* 0.45 + (64 * HotbarBoxCtr)), *WindowHeight * 0.91, 64, 64);
            HotbarBoxCtr++;
    }


    if(*WindowWidth < 1775 && *WindowHeight < 1000){
        SDL_SetWindowSize(window, 300, 364);
    }
    else{
        SDL_SetWindowMinimumSize(window, 300, 364);
    }




    return 1;
}

int main(int argc, char* argv[]) {

    //Global Inits
    GlobalInit();

    //Hotbar Inits
    HotbarInit();

    //Learning Pod Inits
    LearningPodInit();

    //Player1 inits
    Player1->ChangeWDst(100, 100, 64, 64);
    Player1->ChangeWSrc(0, 0, 64, 64);




    while(running){
        start = SDL_GetPerformanceCounter();
        while(SDL_PollEvent(input)){
            if(input->type == SDL_QUIT){
                running = false;
            }
        }

        Input();
        ProportionsUpdate();
        Player1->NxtFrame(1);

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        
        
        Player1->PlayerRender();
        Background->Render();
        Background->BlockAnimation(0);


        Hotbar->Show();

        for(Block* LP_Render : LearningPods){
            LP_Render->Render();
            LP_Render->BlockAnimation(1);
            LP_Render->UseBlock(Player1);
        }
        Background->UseBlock(Player1);

        cursor->Update();
        std::cout<<SDL_GetError();
        end = SDL_GetPerformanceCounter();
        std::cout<< 1.0f / ReturnFrameRate() << "\n";
    }
    // Close and destroy the window
        
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}