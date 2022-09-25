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
SDL_Rect SizePlace_Menu = {0, 0, 600, 600};
bool ShowMenu = false;

int MenuWidth = 1080/2-100;
int MenuHeight = 720/2-100;

SDL_Event input;
bool* running = new bool(true);

//Player
Player User("Sima", "../res/userGray.png", renderer);






//Vectors
std::vector <Entity*> Entities;
std::vector <Entity*> Menu_Entities;

//Resources
Event Menu(renderer, SizePlace_Menu, Menu_Entities);
Mouse cursor("../res/cursor.png", renderer);
Entity Bg("../res/bg.png", renderer);
//Menu
Entity *MenuBg = new Entity("../res/bg.png", renderer);


int Input(){
    SDL_PollEvent(&input);
    if(input.type == SDL_QUIT){
        *running = false;
    }
    if(state[SDL_SCANCODE_SPACE]){
        ShowMenu = 0;
    }
    if(state[SDL_SCANCODE_ESCAPE]){
        ShowMenu = 1;
    }
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

    return 1;

}

int main(int argc, char* argv[]) {
    //Other initializations
    logo = IMG_Load("../res/logo.png");
    SDL_SetWindowIcon(window, logo);
    init(window, renderer);

    //Menu Inits
    MenuBg->ChangeWSrc(0, 0, 100, 100);
    MenuBg->ChangeWDst(MenuWidth, MenuHeight, 100, 100);
    Menu.AddEntity(MenuBg);

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
        cursor.Update();


        std::cout<<SDL_GetError();

    }
    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}