#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "../include/entity.h"
#include "../include/event.h"
#include "../include/game.h"

Game::Game(SDL_Event* Event)
:Event(Event)
{

}

void Game::Input(bool *running){
    while(SDL_PollEvent(Event)){
            if(Event->type == SDL_QUIT){
                *running = false;
            }
        }
}