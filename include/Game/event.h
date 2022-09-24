#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "entity.h"
#include "mouse.h"

class Event{
public:
    Event();
    Event(SDL_Renderer *renderer, SDL_Rect SiPl, std::vector <Entity*> entities);
    void AddMouse(Mouse *M);
    void AddEntity(Entity *entity);
    void Show();
    void RenderLoop();
    void Input(bool *running);
    void Window(int num);
private:
    SDL_Renderer *renderer;
    SDL_Rect SiPl;
    std::vector <Entity*> entities;
    Mouse *M;
    SDL_Event* event;
};