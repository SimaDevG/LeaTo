#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "../include/block.h"
#include "../include/button.h"
#include "../include/event.h"
#include "../include/func.h"
#include "../include/mouse.h"
#include "../include/player.h"


class Entity{
public:
    Entity(const char* filePath, SDL_Renderer *renderer);
    Entity();

    bool Update();

    void Render();

    void ChangeSrc(std::string par, int num);
    void ChangeDst(std::string par, int num);

    void ChangeWSrc(int x, int y, int w, int h);
    void ChangeWDst(int x, int y, int w, int h);

    void ChangeDstX(int num);
    void ChangeDstY(int num);

    SDL_Texture* ReturnTex();
    SDL_Rect* ReturnSrc();
    SDL_Rect* ReturnDst();
    SDL_Renderer* ReturnRenderer();

    int CheckCollision(Entity *Entity);
protected:
    SDL_Rect* src = new SDL_Rect { 0, 0, 1920, 1080 };
    SDL_Rect* dst = new SDL_Rect { 0, 0, 1920, 1080 };
    SDL_Texture* texture;
    SDL_Renderer *renderer;

};

void RenderVector(std::vector<Entity> ent);
void RenderVectorP(std::vector<Entity*> ent);
void RenderVectorBlocks(std::vector<Block*> blk);