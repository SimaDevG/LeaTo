#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "../../include/Game/entity.h"
#include "../../include/Game/func.h"

//Creating the texture/entity
Entity::Entity(const char* filePath, SDL_Renderer *renderer)
    :texture(NULL), renderer(renderer)
{
    texture = loadIMG(filePath, renderer);
}

Entity::Entity(){

};



//Renders out according to src and dst
void Entity::Render(){
    SDL_RenderCopy(renderer, texture, src, dst);
}

//Renders all the entities in a vector
void RenderVector(std::vector<Entity> ent){
    for(Entity e : ent){
        e.Render();
    }
}

//Renders all the entities in a vector (Pointers)
void RenderVectorP(std::vector<Entity*> ent){
    for(Entity* e : ent){
        e->Render();
    }
}



//Changes the objects src SDL_Rect
void Entity::ChangeSrc(std::string par, float num){
    if(par == "x"){
        src->x = num;
    }
    else if (par == "y"){
        src->y = num;
    }
    else if(par == "w"){
        src->w = num;
    }
    else if(par == "h"){
        src->h = num;
    }
    else {
        std::cout<<"Not a valid input"<<"/n";
    }
}



//Changes the objects dst SDL_Rect
void Entity::ChangeDst(std::string par, float num){
    if(par == "x"){
        dst->x = num;
    }
    else if (par == "y"){
        dst->y = num;
    }
    else if(par == "w"){
        dst->w = num;
    }
    else if(par == "h"){
        dst->h = num;
    }
    else {
        std::cout<<"Not a valid input"<<"/n";
    }
}

//Changes the whole src SDL_Rect
void Entity::ChangeWSrc(int x, int y, int w, int h){
    src->x = x;
    src->y = y;
    src->w = w;
    src->h = h;
}

//Changes the whole dst SDL_Rect
void Entity::ChangeWDst(int x, int y, int w, int h){
    dst->x = x;
    dst->y = y;
    dst->w = w;
    dst->h = h;
}

//Changes X of dst SDL_Rect
void Entity::ChangeDstX(int num){
        dst->x += num;
}


//Changes Y of dst SDL_Rect
void Entity::ChangeDstY(int num){
    dst->y += num;
}

SDL_Texture* Entity::ReturnTex(){
    return texture;
}

SDL_Rect* Entity::ReturnSrc(){
    return src;
}

SDL_Rect* Entity::ReturnDst(){
    return dst;
}

SDL_Renderer* Entity::ReturnRenderer(){
    return renderer;
}