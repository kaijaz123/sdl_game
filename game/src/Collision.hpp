#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <tuple>

class Collision
{
public:
    bool yCollision = false, xCollision = false;
    bool collide = false;

    Collision() = default;
    ~Collision() {};

    void CollideXY(SDL_Rect obj_A, SDL_Rect obj_B)
    {
        if 
        (
            obj_A.y + obj_A.h >= obj_B.y ||
            obj_A.y >= obj_B.y        
        )
        { 
            xCollision = false;
            yCollision = true;
        }
        else
        {
            xCollision = true;
            yCollision = false;
        }
    }

    std::tuple<bool, bool, bool> Collide(SDL_Rect obj_A, SDL_Rect obj_B)
    {
        collide = false;
        xCollision = false;
        yCollision = false;

        if
        (
            obj_A.x + obj_A.w >= obj_B.x &&
            obj_B.x + obj_B.w >= obj_A.x &&
            obj_A.y + obj_A.h >= obj_B.y &&
            obj_B.y + obj_B.h >= obj_A.y
        )
        {
            collide = true;
            CollideXY(obj_A, obj_B);
        }
        return std::make_tuple(collide, xCollision, yCollision);
    }
};