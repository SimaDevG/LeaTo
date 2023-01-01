#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <functional>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <string>


#include "../include/block.h"
#include "../include/user.h"
#include "../include/func.h"
#include "../include/utility.h"



/*To Do
- Get SDL TTF
- Fix Pods focus mod
- Fix Hotbar Focus (Unfocus)
- Looks
- Networking
*/


/*------------------------------------------*/
//SDL Initializations

        //SDL
int WindowWidth = 300;
int WindowHeight = 364;
SDL_Surface *logo;
SDL_Window* window = SDL_CreateWindow( "LeaTo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_RESIZABLE);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);



/*------------------------------------------*/
//LeaTo variables
        //Input
const Uint8 *state = SDL_GetKeyboardState(NULL);
SDL_Event *input = new SDL_Event;


        //Functionality
bool running = true;


        //Window



        //FPS
Uint64 start;
Uint64 end;



        //Vectors
std::vector <Entity*> Entities;
std::vector <Entity*> Hotbar_Entities; //Hotbar (1, 2, 3, 4)
std::vector <User*> Users;



        //Resources
Entity *UseIcon = new Entity("../res/UseIcon.png", renderer);
Mouse *cursor = new Mouse("../res/cursor.png", renderer);



        //Background & Main Menu


        //Users
User *ThisUser = new User("Sima", "../res/owlSpr.png", renderer, SDL_Rect {0, 0, WindowWidth, WindowHeight});


        //Hotbar
Hotbar *hotbar = new Hotbar(renderer);
Uint32 hotbarTimeout;


        //Learning Pods
std::vector <Block*> Pods;
/*------------------------------------------*/







int GlobalInit(){

    //SDL & Window
    init(window, renderer);
    SDL_SetWindowMinimumSize(window, 300, 364);
    SDL_SetWindowMaximumSize(window, 300, 364);
    SDL_SetWindowSize(window, 300, 364);

    //In the future to create a logo
    //Window logo
    /*logo = IMG_Load("../res/logo.png");
    SDL_SetWindowIcon(window, logo);*/


    //Background (Block)


    //Users
    Users.push_back(ThisUser); //Add this user to User Array
    ThisUser->ModifyPixelW(64); //User Pixel Size
    ThisUser->ModifyLoops(40); //Amount of loops per each frame loop


    return 0;
}

int HotbarInit(){
    for(int box = 0; box < 3; box++){           //Three boxes so three loops
        hotbar->AddEntity(new Entity("../res/hotbarbox.png", renderer));         //Add entity to Hotbar Vector
        hotbar->ReturnEntity(box)->ChangeWSrc(0, 0, 64, 64);                     //Change Entity ^ src size
        hotbar->ReturnEntity(box)->ChangeWDst(54 + (64 * box), 290, 64, 64);     // Change Entity ^ dst size (Width according to box num)
    }

    return 0;
}

int LearningPodInit(){
    int BlockPosX =  WindowWidth * 0.25;   //Block Position in the window (In relation to the window size)
    int BlockPosY = WindowHeight * 0.1;

    int ButtonPosX = BlockPosX + 43;       //  Button Position in the Block
    int ButtonPosY = BlockPosY + 43;

    /*int MenuPosX = BlockPosX + 12.5;         // Menu Position of the Block
    int MenuPosY = BlockPosY + 12.5;*/ //Not in use right now
    Button *button = new Button(new SDL_Rect {ButtonPosX, ButtonPosY, 64, 64}, renderer, state, SDL_SCANCODE_E);    //Button 
    button->AddFunction([]{Users[0]->focusMode();});
    button->AddMouse(cursor);

    //Entity *menuBackground = new Entity("../res/LPMenu.png", renderer);   menuBackground->ChangeWDst(MenuPosX, MenuPosY, 125, 125);          //Menu Background //Not Necessary Right Now, Later on For Modifying Time.
    std::vector <Entity*> *menuEntities = new std::vector <Entity*>;                                                                           //Entities in a Menu
    Event *menu = new Event(renderer, *menuEntities);                                                                                          //Menu
    //menu->AddEntity(menuBackground);                                                                                                         //Background to Menu ^

    Block *block = new Block("../res/LearningPod.png", renderer, button, menu);                                                                //Block
    block->ChangeWDst(BlockPosX, BlockPosY, 150, 150);                                                                                         //Size Dst                                                                                                      //
    block->ChangeWSrc(0, 0, 128, 128);                                                                                                         //Size Src  
    block->AddAnimationFrames(8);                                                                                                              //8 Animation Frames in Block
    block->AddBlockNumber(1);

    Pods.push_back(block);                                                                                                                     //Block Added to Pods


    return 0;
}

int Input(){
    int Cooldown = 125; //(Hotbar)
//User
    //User Movement
    if(state[SDL_SCANCODE_D]){
        Users[0]->MoveX(3);
    }
    if(state[SDL_SCANCODE_A]){
        Users[0]->MoveX(-3);
    }
    if(state[SDL_SCANCODE_S]){
        Users[0]->MoveY(3);
    }
    if(state[SDL_SCANCODE_W]){
        Users[0]->MoveY(-3);
    }


/*------------------------------------------*/
//Hotbar
    //Hotbar Focus
    if(state[SDL_SCANCODE_1] && SDL_GetTicks() >= hotbarTimeout){
        hotbar->setinUse(0, !(*hotbar->ReturninUse()[0]));
        hotbarTimeout = SDL_GetTicks() + Cooldown;
    }
    if(state[SDL_SCANCODE_2] && SDL_GetTicks() >= hotbarTimeout){
        hotbar->setinUse(1, !(*hotbar->ReturninUse()[1]));
        hotbarTimeout = SDL_GetTicks() + Cooldown;
    }
    if(state[SDL_SCANCODE_3] && SDL_GetTicks() >= hotbarTimeout){
        hotbar->setinUse(2, !(*hotbar->ReturninUse()[2]));
        hotbarTimeout = SDL_GetTicks() + Cooldown;
    }
    return 0;

}

float ReturnFrameRate(){
    return (end - start) / (float)SDL_GetPerformanceFrequency(); //Calculation of FPS
}

int main(int argc, char* argv[]) {

    //Lambda Function For Initializer Functions
        //Global Inits
        GlobalInit();

        //Hotbar Inits
        HotbarInit();

        //Learning Pod Inits
        LearningPodInit();

    //Application Loop
    while(running){
        start = SDL_GetPerformanceCounter(); //FPS Counter Start

        while(SDL_PollEvent(input)){  //SDL_QUIT Input
            if(input->type == SDL_QUIT){
                running = false;
            }
        }

        Input(); //SDL_Scancode Input (State)
 
        SDL_RenderPresent(renderer);    //Updates renderer (Changes made since last rendering)
        SDL_RenderClear(renderer);      //Clears Window
        //Background->Render();           //Renders Background
        //Background->BlockAnimation(0);  //Background Animation (If there is)


        //Pods Processes
        Pods[0]->BlockAnimation(1);

        //Background Menu User Ability
        //Background->UseBlock(Users[0]);


        Users[0]->UserRender(1);  //User Rendering And Frame Update  

        Pods[0]->UseBlock(Users[0]);

        //Cursor & Hotbar
        hotbar->RenderHotbar();
        cursor->Update();
        //FPS And Get Errors
        std::cout<<SDL_GetError();
        end = SDL_GetPerformanceCounter();
        //std::cout<< 1.0f / ReturnFrameRate() << "\n";
    }
/*------------------------------------------*/
//Quitting
    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}