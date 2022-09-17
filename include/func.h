#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "entity.h"

SDL_Texture* loadIMG(const char* filepath, SDL_Renderer* renderer);
void bgFillC(const char* filepath, SDL_Renderer* renderer);
void bgFill(const char* filepath, SDL_Renderer* renderer);