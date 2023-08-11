#pragma once

#include <SDL2/SDL.h>
#include "ECS.hpp"

class TransformComponent : public Component
{
public:
    int position_x, position_y;
    int velocity_x, velocity_y;
    int texPos_x, texPos_y;
    int size;
    int scale;
    int speed;

    TransformComponent() = default;
    ~TransformComponent() {};

    TransformComponent(int tP_x, int tP_y, int pos_x, int pos_y, int sz, int sc, int sp, int ax, int ay)
    {
        texPos_x = tP_x;
        texPos_y = tP_y;
        position_x = pos_x + ax;
        position_y = pos_y + ay;
        size = sz;
        scale = sc;
        speed = sp;
        
        velocity_x = velocity_y = 0;
    }

    void update() override
    {
        position_x += static_cast<int>(velocity_x * speed);
        position_y += static_cast<int>(velocity_y * speed);
    }

private:
};