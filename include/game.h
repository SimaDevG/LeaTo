#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "../include/entity.h"
#include "../include/event.h"

class Game : public Event{
public: 
    Game(SDL_Event* Event);
    void Input(bool *running);
private:
    SDL_Event* Event;
};