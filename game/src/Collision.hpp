#pragma once

#include <iostream>
#include <SDL2/SDL.h>

class Collision
{
public:
    Collision() = default;
    ~Collision() {};

    bool Collide(SDL_Rect obj_A, SDL_Rect obj_B)
    {
        std::cout << "Player xo: " << obj_A.x << std::endl;
        std::cout << "Player yo: " << obj_A.y << std::endl;
        std::cout << "Object xo: " << obj_B.x << std::endl;
        std::cout << "Object yo: " << obj_B.y << std::endl;
        std::cout << "Player x: " << obj_A.x + obj_A.w << std::endl;
        std::cout << "Player y: " << obj_A.y + obj_A.h << std::endl;
        std::cout << "Object x: " << obj_B.x + obj_B.w<< std::endl;
        std::cout << "Object y: " << obj_B.y + obj_B.h << std::endl;
        if
        (
            obj_A.x + obj_A.w >= obj_B.x &&
            obj_B.x + obj_B.w >= obj_A.x &&
            obj_A.y + obj_A.h >= obj_B.y &&
            obj_B.y + obj_B.h >= obj_A.y
        )
        { return true; }
        return false;
    }
};