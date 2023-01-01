#pragma once
#include "user.h"

class Event;

/*Mouse*/
class Mouse : public Entity{
public:
    Mouse(const char* filePath, SDL_Renderer *rendeclererm);
    void Update();
    SDL_Rect* GetPos();
    bool CheckPos(int x, int y);
private:
    SDL_Rect pos;
};




















/*Button*/
class Button : public Entity{
public:
    Button(SDL_Rect *buttonPos, SDL_Renderer* rendrr, const Uint8 *pressed /*State For Checking*/, SDL_Scancode key /*Activation Key*/);
    int AddEvent(SDL_Event *event);
    int AddMouse(Mouse *M);
    int AddFunction(void func());
    int AddGButton(const char *filePath); //Add graphical button
    bool Pressed(SDL_Rect *rect);
    bool ModifyCooldown (int cooldown);
    void AddEvent(Event* EventToAdd);

private:
    inline static Uint64 timeout = 0;
    const Uint8 *state;
    SDL_Scancode activationKey;
    SDL_Event *event;
    Mouse *GlobalMouse;
    int Cooldown = 200;
    Event *EventAdd;
        
    void(*function)();   // Pointer to a function
};

























/*Event*/
class Event{
public:
    Event();
    Event(SDL_Renderer *renderer, std::vector <Entity*> entities);
    void AddMouse(Mouse *M);
    void AddEntity(Entity *entity);
    std::vector <Entity*> ReturnEntities();
    Entity* ReturnEntity(int num);
    int Show();
    void AddButtonV(std::vector <Button*> buttonVector);
    void AddButton(Button* buttonAdd);
    SDL_Renderer *renderer;
    std::vector <Entity*> entities;
    std::vector <Button*> buttons;
    Mouse *M;
    SDL_Event* event;
};

/*Hotbar*/
class Hotbar : public Event{
public:
    Hotbar(SDL_Renderer *renderer);
    int RenderHotbar();
    std::vector <bool*> ReturninUse();
    int setinUse(int, bool);
private:
    std::vector <bool*> inUse = {new bool(false), new bool(false), new bool(false)}; //Three Boxes, None in Use
};