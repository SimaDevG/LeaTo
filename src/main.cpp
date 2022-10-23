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
1. Get Right Proportions On Learningpods
2. Fix Hotbar
3. Fix Main Menu Button
4. Fix LearningPods focus mod
5. Main Communication Table
6. Looks
7. Networking
Set so that if window size gets to a sudden point, it will go down even more, so that only the user is seen with the learning pod, including the timer.

Learningpod timer for study sessions


*/



/*git remote -v to go to website repo*/


//SDL Initializations
int *WindowWidth =  new int(1775);
int *WindowHeight = new int (1000);
SDL_Surface *logo;
SDL_Window* window = SDL_CreateWindow( "LeaTo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, *WindowWidth, *WindowHeight, SDL_WINDOW_RESIZABLE);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

//LeaTo variables
const Uint8 *state = SDL_GetKeyboardState(NULL);
bool ShowMenu = false;
SDL_Event *input = new SDL_Event;
bool* running = new bool(true);

//Player
Player *User = new Player("Sima", "../res/userGray.png", renderer);

//Vectors
std::vector <Entity*> Entities;
std::vector <Entity*> Menu_Entities; //Menu (ESC)
std::vector <Entity*> Hotbar_Entities; //Hotbar (1, 2, 3, 4)

//Resources
Entity *UseIcon = new Entity("../res/UseIcon.png", renderer);
Mouse *cursor = new Mouse("../res/cursor.png", renderer);
Entity *Bg = new Entity("../res/bg.png", renderer);

//Menu
Event Menu(renderer, Menu_Entities);
Entity *MenuBg = new Entity("../res/bg.png", renderer);
int MenuWidth = 600;
int MenuHeight = 333;

int GlobalInit(){

    init(window, renderer);
    SDL_SetWindowMinimumSize(window, 300, 364);

    //Window logo
    logo = IMG_Load("../res/logo.png");
    SDL_SetWindowIcon(window, logo);


    return 1;
}

int MenuInit(){
    MenuBg->ChangeWSrc(0, 0, 100, 100);
    MenuBg->ChangeWDst(374, 33, MenuWidth, MenuHeight);
    Menu.AddEntity(MenuBg);
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

        Entity *tempMenuBG = new Entity("../res/blue.png", renderer);   tempMenuBG->ChangeWDst(MenuPosX, 233, 300, 300);
        std::vector <Entity*> *tempMenuEntities = new std::vector <Entity*>;
        Event *tempMenu = new Event(renderer, *tempMenuEntities);
        tempMenu->AddEntity(tempMenuBG);

        Block *TempBlock = new Block("../res/LearningPod.png", renderer, tempButton, tempMenu);
        TempBlock->ChangeWDst(BlockPos, 333, 128, 128);
        TempBlock->AddBlockNumber(BlNr);
        TempBlock->ChangeWSrc(0, 0, 128, 128);
        TempBlock->AddAnimationFrames(4);

        LearningPods.push_back(TempBlock);
    }
    return 3;
}



int Input(){
    //Menu
    if(state[SDL_SCANCODE_SPACE]){
        ShowMenu = 0;
    }
    if(state[SDL_SCANCODE_ESCAPE]){
        ShowMenu = 1;
    }
    //Movement
    if(state[SDL_SCANCODE_D]){
        User->MoveX(3);
    }
    if(state[SDL_SCANCODE_A]){
        User->MoveX(-3);
    }
    if(state[SDL_SCANCODE_S]){
        User->MoveY(3);
    }
    if(state[SDL_SCANCODE_W]){
        User->MoveY(-3);
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

        Block->ReturnBlockButton()->ChangeWDst(BlockUpdateX + 32, BlockUpdateY + 50, 64, 64);

        Block->ReturnBlockEvent()->ReturnEntities()[0]->ChangeWDst(BlockUpdateX - 86, BlockUpdateY - 100, 300, 300);

    }

    //Hotbar 
    for(Entity *HotbarBox : Hotbar->ReturnEntities()){
            HotbarBox->ChangeWDst((*WindowWidth* 0.45 + (64 * HotbarBoxCtr)), *WindowHeight * 0.9, 64, 64);
            HotbarBoxCtr++;
    }


    if(*WindowWidth < 1775 && *WindowHeight < 1000){
        SDL_SetWindowSize(window, 300, 364);
    }

    else if(*WindowWidth < 1775){
        SDL_SetWindowMinimumSize(window, 1775, 364);
    }

    else if(*WindowHeight < 1000){
        SDL_SetWindowMinimumSize(window, 300, 1000);
    }
    else{
        SDL_SetWindowMinimumSize(window, 300, 364);
    }




    return 1;
}

int main(int argc, char* argv[]) {

    //Global Inits
    GlobalInit();

    //Menu Inits
    MenuInit();

    //Hotbar Inits
    HotbarInit();

    //Learning Pod Inits
    LearningPodInit();

    //User inits
    User->ChangeWDst(100, 100, 64, 64);
    User->ChangeWSrc(0, 0, 64, 64);




    while(*running){
        while(SDL_PollEvent(input)){
            if(input->type == SDL_QUIT){
                *running = false;
            }
        }

        Input();
        ProportionsUpdate();
        User->NxtFrame();

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);



        if(ShowMenu == true){
          Menu.Show();
        }
        Hotbar->Show();

        User->UserRender();
        for(Block* LP_Render : LearningPods){
            LP_Render->Render();
            LP_Render->BlockAnimation();
            LP_Render->UseBlock(User);
        }


        cursor->Update();
        std::cout<<SDL_GetError();

    }
    // Close and destroy the window
        
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}