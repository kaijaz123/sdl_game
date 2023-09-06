#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <tuple>

class Collision
{
public:

    Collision() = default;
    ~Collision() {};

    bool Collide(SDL_Rect obj_A, SDL_Rect obj_B)
    {
        if
        (
            obj_A.x + obj_A.w >= obj_B.x &&
            obj_B.x + obj_B.w >= obj_A.x &&
            obj_A.y + obj_A.h >= obj_B.y &&
            obj_B.y + obj_B.h >= obj_A.y
        )
        {
            return true;
        }
        return false;
    }
};