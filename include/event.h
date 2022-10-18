#pragma once
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

class Event{
public:
    Event();
    Event(SDL_Renderer *renderer, std::vector <Entity*> entities);
    void AddMouse(Mouse *M);
    void AddEntity(Entity *entity);
    std::vector <Entity*> ReturnEntities();
    Entity* ReturnEntity(int num);
    int Show();

private:
    SDL_Renderer *renderer;
    std::vector <Entity*> entities;
    Mouse *M;
    SDL_Event* event;
};