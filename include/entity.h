#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

class Entity{
public:
    Entity(const char* filePath, SDL_Renderer *renderer);
    Entity();

    bool Update();

    void Render();

    void ChangeSrc(std::string par, float num);
    void ChangeDst(std::string par, float num);

    void ChangeWSrc(int x, int y, int w, int h);
    void ChangeWDst(int x, int y, int w, int h);

    void ChangeDstX(int num);
    void ChangeDstY(int num);

    SDL_Texture* ReturnTex();
    SDL_Rect* ReturnSrc();
    SDL_Rect* ReturnDst();
protected:
    SDL_Rect* src;
    SDL_Rect* dst;
    SDL_Texture* texture;
    SDL_Renderer *renderer;

};

void RenderVector(std::vector<Entity> ent);
void RenderVectorP(std::vector<Entity*> ent);