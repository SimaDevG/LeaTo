#pragma once
#include "player.h"

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
    Button(SDL_Rect *buttonPos, const char *filePath, SDL_Renderer* rendrr, const Uint8 *pressed, SDL_Scancode key, SDL_Event *event);
    int AddMouse(Mouse *M);
    bool Pressed(SDL_Rect *rect, bool change, bool showEvent = false);
    bool ModifyCooldown (int cooldown);
    void AddEvent(Event* EventToAdd);

private:
    inline static Uint64 timeout = 0;
    const Uint8 *state;
    SDL_Scancode activationKey;
    SDL_Event *E;
    Mouse *GlobalMouse;
    int Cooldown = 200;

    Event *EventAdd;
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

private:
    SDL_Renderer *renderer;
    std::vector <Entity*> entities;
    std::vector <Button*> buttons;
    Mouse *M;
    SDL_Event* event;
};