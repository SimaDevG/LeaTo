#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>


#include "../include/mouse.h"




Mouse::Mouse(const char* filePath, SDL_Renderer *rendererm)
{
    renderer = rendererm;
    texture = loadIMG(filePath, renderer);
    src->x = 0;
    src->y = 0;
    src->w = 64;
    src->h = 64;

    dst->x = 0;
    dst->y = 0;
    dst->w = 25;
    dst->h = 25;

    SDL_ShowCursor(false);
}

void Mouse::Update(){
    SDL_GetMouseState(&dst->x, &dst->y);
    SDL_RenderCopy(renderer, texture, src, dst);
}

SDL_Rect* Mouse::GetPos(){
    SDL_GetMouseState(&pos.x, &pos.y);
    return &pos;
} 

bool Mouse::CheckPos(int x, int y){
    SDL_GetMouseState(&pos.x, &pos.y);
    if(pos.x == x && pos.y == y){
        return true;
    }
    else{
        return false;
    }
}