#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
/*#include <SDL2/SDL_ttf.h>*/
#include <iostream>
#include <vector>
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
int *WindowWidth = new int(1775);
int *WindowHeight = new int(1000);
SDL_Surface *logo;
SDL_Window* window = SDL_CreateWindow( "LeaTo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, *WindowWidth, *WindowHeight, SDL_WINDOW_RESIZABLE);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);



/*------------------------------------------*/
//LeaTo variables
        //Input
const Uint8 *state = SDL_GetKeyboardState(NULL);
SDL_Event *input = new SDL_Event;


        //Functionality
bool running = true;


        //Window
//WindowWidth =  new 1775;
//WindowHeight = new int (1000);



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
Block *Background = new Block("../res/bg.png", renderer, new Button(new SDL_Rect {}, "../res/UseIcon.png", renderer, state, SDL_SCANCODE_ESCAPE, NULL, input), new Event(renderer, std::vector <Entity*> {}));




        //Users
User *ThisUser = new User("Sima", "../res/owlSpr.png", renderer);


        //Hotbar
Event *Hotbar = new Event(renderer, Hotbar_Entities);


        //Learning Pods
std::vector <Block*> Pods;
/*------------------------------------------*/








int GlobalInit(){

    //SDL & Window
    init(window, renderer);
    SDL_SetWindowMinimumSize(window, 300, 364);
    SDL_SetWindowMaximumSize(window, 1775, 1000);

    //In the future to create a logo
    //Window logo
    /*logo = IMG_Load("../res/logo.png");
    SDL_SetWindowIcon(window, logo);*/


    //Background (Block)
    Background->ReturnBlockEvent()->AddEntity(new Entity("../res/LPMenu.png", renderer));  //Block returns -> Event returns -> Entity
    Background->ReturnBlockEvent()->ReturnEntity(0)->ChangeWDst(100, 100, 1575, 800); // ^ Entity Size
    Background->ReturnBlockEvent()->AddButton(new Button(new SDL_Rect  {500, 500, 64, 64}, "../res/UseIcon.png", renderer, state, SDL_SCANCODE_ESCAPE, NULL, input)); //Block returns -> Event Returns -> Button
    Background->ReturnBlockButton()->ModifyCooldown(150); //Button Cooldown Change (Cooldown for another press)

    //Users
    Users.push_back(ThisUser); //Add this user to User Array
    ThisUser->ModifyPixelW(64); //User Pixel Size
    ThisUser->ModifyLoops(40); //Amount of loops per each frame loop


    return 0;
}

int HotbarInit(){
    for(int box = 0; box < 3; box++){               //Three boxes so three loops
        Hotbar->AddEntity(new Entity("../res/hotbarbox.png", renderer));        //Add entity to Hotbar Vector
        Hotbar->ReturnEntity(box)->ChangeWSrc(0, 0, 64, 64);                    //Change Entity ^ src size
        Hotbar->ReturnEntity(box)->ChangeWDst(444 + 64 * box, 756, 64, 64);     // Change Entity ^ dst size (Width according to box num)
    }

    return 0;
}

int LearningPodInit(){
    int BlockPos =  *WindowWidth * 0.12;   //Block Position in the window (In relation to the window size)
    int ButtonPosX = BlockPos + 32;       //  Button Position in the Block
    int MenuPosX = BlockPos - 86;         // Menu Position of the Block



    Button *button = new Button(new SDL_Rect {ButtonPosX, 383, 64, 64}, "../res/UseIcon.png", renderer, state, SDL_SCANCODE_E, NULL ,input);   //Button 
    button->AddMouse(cursor);

    Entity *menuBackground = new Entity("../res/LPMenu.png", renderer);   menuBackground->ChangeWDst(MenuPosX, 233, 300, 300);                 //Menu Background
    std::vector <Entity*> *menuEntities = new std::vector <Entity*>;                                                                           //Entities in a Menu
    Event *menu = new Event(renderer, *menuEntities);                                                                                          //Menu
    menu->AddEntity(menuBackground);                                                                                                           //Background to Menu ^

    Block *block = new Block("../res/LearningPod.png", renderer, button, menu);                                                                //Block
    block->ChangeWDst(BlockPos, 333, 128, 128);                                                                                                //Size Dst                                                                                                      //
    block->ChangeWSrc(0, 0, 128, 128);                                                                                                         //Size Src  
    block->AddAnimationFrames(8);                                                                                                              //8 Animation Frames in Block
    block->AddBlockNumber(1);

    Pods.push_back(block);                                                                                                                     //Block Added to Pods


    return 0;
}

int Input(){

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
    if(state[SDL_SCANCODE_1]){
        for(int box = 0; box < 3; ++box){
            Hotbar->ReturnEntity(box)->ChangeSrc("x", 0); //Resets all other
        }
        Hotbar->ReturnEntity(0)->ChangeSrc("x", 64);  //Sets the one used (First, 0)
    }
    if(state[SDL_SCANCODE_2]){
        for(int box = 0; box < 3; ++box){
            Hotbar->ReturnEntity(box)->ChangeSrc("x", 0); //--||--
        }
        Hotbar->ReturnEntity(1)->ChangeSrc("x", 64);      //--||--
    }
    if(state[SDL_SCANCODE_3]){
        for(int box = 0; box < 3; ++box){
            Hotbar->ReturnEntity(box)->ChangeSrc("x", 0);   //--||--
        }
        Hotbar->ReturnEntity(2)->ChangeSrc("x", 64);        //--||--
    }

    return 0;

}

float ReturnFrameRate(){
    return (end - start) / (float)SDL_GetPerformanceFrequency(); //Calculation of FPS
}

int ProportionsUpdate(){
    int BlockUpdateX; //Change of X of Block
    int BlockUpdateY; //Change of Y of Block
    int HotbarBoxCtr = 0; //Hotbar Choice
    
    //Getting current window size
    SDL_GetWindowSize(window, WindowWidth, WindowHeight);

    //Proportions on block
    for(Block* Block : Pods){
        BlockUpdateX = (*WindowWidth * (0.12 * Block->ReturnBlockNumber())); //Calculation of X
        BlockUpdateY = *WindowHeight * 0.3;                                  //Calculation of Y

        Block->ChangeWDst(BlockUpdateX, BlockUpdateY, 128, 128);            //Block Changes

        Block->ReturnBlockButton()->ChangeWDst(BlockUpdateX + 32, BlockUpdateY + 32, 64, 64);           //Block Button Changes (According to var X & Y)

        Block->ReturnBlockEvent()->ReturnEntities()[0]->ChangeWDst(BlockUpdateX - 86, BlockUpdateY - 100, 300, 300);      //Block Event Changes (According to var X & Y)

    }

    //Hotbar 
    for(Entity *HotbarBox : Hotbar/*Event Class*/->ReturnEntities()){                                                              //Each Hotbar
            HotbarBox->ChangeWDst((*WindowWidth* 0.45 + (64 * HotbarBoxCtr)), *WindowHeight * 0.91, 64, 64);
            HotbarBoxCtr++;
    }


    //Window Settings According to Size
    if(*WindowWidth < 1775 && *WindowHeight < 1000){
        SDL_SetWindowSize(window, 300, 364);
    }
    else{
        SDL_SetWindowMinimumSize(window, 300, 364);
    }

    return 0;
}

int main(int argc, char* argv[]) {

    //Lambda Function For Initializer Functions
    /*[](){*/
        //Global Inits
        GlobalInit();

        //Hotbar Inits
        HotbarInit();

        //Learning Pod Inits
        LearningPodInit();
    /*};*/

    //Application Loop
    while(running){
        start = SDL_GetPerformanceCounter(); //FPS Counter Start

        while(SDL_PollEvent(input)){  //SDL_QUIT Input
            if(input->type == SDL_QUIT){
                running = false;
            }
        }

        Input(); //SDL_Scancode Input (State)
        ProportionsUpdate();    //Updates Entities in Window According to Size
        Users[0]->NxtFrame(1);  //User Frame Update

        SDL_RenderPresent(renderer);    //Updates renderer (Changes made since last rendering)
        SDL_RenderClear(renderer);      //Clears Window
        
        
        Users[0]->UserRender();         //Renders User (first in User Vector)
        Background->Render();           //Renders Background
        //Background->BlockAnimation(0);  //Background Animation (If there is)


        //Pods Processes
        Pods[0]->Render();
        Pods[0]->BlockAnimation(1);
        Pods[0]->UseBlock(Users[0]);

        //Background Menu User Ability
        Background->UseBlock(Users[0]);

        //Cursor & Hotbar
        cursor->Update();
        Hotbar->Show();

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