#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../include/block.h"
#include "../include/button.h"
#include "../include/entity.h"
#include "../include/event.h"
#include "../include/mouse.h"
#include "../include/player.h"


SDL_Texture* loadIMG(const char* filepath, SDL_Renderer* renderer);
void init(SDL_Window *window, SDL_Renderer *renderer);
bool checkCollision(SDL_Rect *rect1, SDL_Rect *rect2);