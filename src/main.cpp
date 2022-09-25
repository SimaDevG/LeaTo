#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "../include/Game/entity.h"
#include "../include/Game/func.h"
#include "../include/Game/mouse.h"
#include "../include/Game/event.h"
#include "../include/Player/player.h"

//SDL Initializations
SDL_Surface *logo;
SDL_Window* window = SDL_CreateWindow( "LeaTo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1080, 720, SDL_WINDOW_RESIZABLE);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

//LeaTo variables
const Uint8 *state = SDL_GetKeyboardState(NULL);
bool ShowMenu = false;
SDL_Event input;
bool* running = new bool(true);

//Player
Player User("Sima", "../res/userGray.png", renderer);






//Vectors
std::vector <Entity*> Entities;
std::vector <Entity*> Menu_Entities; //Menu (ESC)
std::vector <Entity*> Hotbar_Entities; //Hotbar (1, 2, 3, 4)

//Resources

Mouse cursor("../res/cursor.png", renderer);
Entity Bg("../res/bg.png", renderer);

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
    std::cout<<"For loop done in Hotbar Init";
    return 1;
}




int Input(){
    SDL_PollEvent(&input);
    if(input.type == SDL_QUIT){
        *running = false;
    }
    //Menu
    if(state[SDL_SCANCODE_SPACE]){
        ShowMenu = 0;
    }
    if(state[SDL_SCANCODE_ESCAPE]){
        ShowMenu = 1;
    }
    //Movement
    if(state[SDL_SCANCODE_D]){
        User.MoveX(1);
    }
    if(state[SDL_SCANCODE_A]){
        User.MoveX(-1);
    }
    if(state[SDL_SCANCODE_S]){
        User.MoveY(1);
    }
    if(state[SDL_SCANCODE_W]){
        User.MoveY(-1);
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

    //User inits
    User.ChangeWDst(540, 360, 64, 64);
    User.ChangeWSrc(0, 0, 64, 64);




    while(*running){
        SDL_PollEvent(&input);
        if(input.type == SDL_QUIT){
            *running = false;
        }
        Input();
        User.NxtFrame();
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        if(ShowMenu == true){
          Menu.Show();
        }

        User.UserRender();
        if(Hotbar.Show()!=1){
            std::cout<<"Something went wrong here...";
        }
        cursor.Update();


        std::cout<<SDL_GetError();

    }
    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}