#pragma once

#include <iostream>
#include <SDL2/SDL.h>

class Collision
{
public:
    Collision();
    ~Collision();

    bool Collide(SDL_Rect obj_A, SDL_Rect obj_B)
    {
        if
        (
            obj_A.y + obj_A.h >= obj_B.y ||
            obj_A.y <= obj_B.y + obj_B.h ||
            obj_A.x + obj_A.w >= obj_B.w ||
            obj_A.x <= obj_B.x + obj_B.w
        )
        { return true; }
        return false;
    }
};