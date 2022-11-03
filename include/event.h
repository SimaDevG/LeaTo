#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "entity.h"
#include "mouse.h"
#include "button.h"



class Event{
public:
    Event();
    Event(SDL_Renderer *renderer, std::vector <Entity*> entities);
    void AddMouse(Mouse *M);
    void AddEntity(Entity *entity);
    std::vector <Entity*> ReturnEntities();
    Entity* ReturnEntity(int num);
    int Show();
    void AddButton(Button* buttonAdd);
    void AddButtonV(std::vector <Button*> buttonVector);

private:
    SDL_Renderer *renderer;
    std::vector <Entity*> entities;
    std::vector <Button*> buttons;
    Mouse *M;
    SDL_Event* event;
};