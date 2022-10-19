#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "block.h"
#include "button.h"
#include "entity.h"
#include "event.h"
#include "mouse.h"


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