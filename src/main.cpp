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



//SDL Initializations
int WindowWidth = 1080;
int WindowHeight = 720;
SDL_Surface *logo;
SDL_Window* window = SDL_CreateWindow( "LeaTo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_RESIZABLE);
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

SDL_Rect SizePlace_Menu = {0, 0, 600, 600};

int MenuInit(){
    MenuBg->ChangeWSrc(0, 0, 100, 100);
    MenuBg->ChangeWDst(374, 33, MenuWidth, MenuHeight);
    Menu.AddEntity(MenuBg);
    return 1;
}


//Hotbar
Event Hotbar(renderer, Hotbar_Entities);
int HotbarInit(){
    for(int box = 0; box < 3; box++){
        Hotbar.AddEntity(new Entity("../res/hotbarbox.png", renderer));
        Hotbar.ReturnEntity(box)->ChangeWSrc(0, 0, 64, 64);
        Hotbar.ReturnEntity(box)->ChangeWDst(444 + 64 * box, 656, 64, 64);
    }
    return 1;
}

//Learning Pods
std::vector <Block*> LearningPods;
SDL_Rect *buttonPos = new SDL_Rect{365, 377, 64, 64};
Button *LPButton = new Button(buttonPos, "../res/UseIcon.png", renderer, state, SDL_SCANCODE_E, input);
Entity *LPMenuBg = new Entity("../res/blue.png", renderer);
std::vector <Entity*> LearningPodEntities;
Event *LearningPodMenu = new Event(renderer, LearningPodEntities);

Block *LearningPod = new Block("../res/LearningPod.png", renderer, LPButton, LearningPodMenu);

int LearningPodInit(){
    for(int ctr1 = 0; ctr1<7; ctr1++){
        LearningPods.push_back(new Block("../res/LearningPod.png", renderer, LPButton, LearningPodMenu));
        LearningPods[ctr1]->ChangeWDst(WindowWidth * (0.1 * ctr1), WindowHeight * 0.2, 128, 128);
    }
    LearningPodMenu->AddEntity(LPMenuBg);
    LPMenuBg->ChangeWDst(233, 233, 333, 333);
    LPButton->AddMouse(cursor);
    LearningPod->ChangeWSrc(0, 0, 128, 128);
    LearningPod->ChangeWDst(333, 333, 128, 128);
    return 1;
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
            Hotbar.ReturnEntity(box)->ChangeSrc("x", 0);
        }
        Hotbar.ReturnEntity(0)->ChangeSrc("x", 64);
    }
    if(state[SDL_SCANCODE_2]){
        for(int box = 0; box < 3; ++box){
            Hotbar.ReturnEntity(box)->ChangeSrc("x", 0);
        }
        Hotbar.ReturnEntity(1)->ChangeSrc("x", 64);
    }
    if(state[SDL_SCANCODE_3]){
        for(int box = 0; box < 3; ++box){
            Hotbar.ReturnEntity(box)->ChangeSrc("x", 0);
        }
        Hotbar.ReturnEntity(2)->ChangeSrc("x", 64);
    }

    return 1;

}

int main(int argc, char* argv[]) {
    //Other initializations
    logo = IMG_Load("../res/logo.png");
    SDL_SetWindowIcon(window, logo);
    init(window, renderer);

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
        User->NxtFrame();
        LearningPod->BlockAnimation();

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        LearningPod->Render();
        LearningPod->UseBlock(User);
        if(ShowMenu == true){
          Menu.Show();
        }



        User->UserRender();
        cursor->Update();
        std::cout<<SDL_GetError();

    }
    // Close and destroy the window
        
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}