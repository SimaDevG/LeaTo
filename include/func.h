#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>



SDL_Texture* loadIMG(const char* filepath, SDL_Renderer* renderer);
void init(SDL_Window *window, SDL_Renderer *renderer);
bool checkCollision(SDL_Rect *rect1, SDL_Rect *rect2);