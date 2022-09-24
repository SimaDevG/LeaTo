#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "../Game/entity.h"

class Player : public Entity{
    Player(std::string username, Entity PlayerE);
    int MoveX(int x);
    int MoveY(int y);
};