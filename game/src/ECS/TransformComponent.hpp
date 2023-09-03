#pragma once

#include <SDL.h>
#include "TileComponent.hpp"
#include "ECS.hpp"

class TransformComponent : public Component
{
public:
    int position_x, position_y;
    int velocity_x, velocity_y;
    int texPos_x, texPos_y;
    int width, height;
    int scale;
    int speed;

    TransformComponent() = default;
    ~TransformComponent() {};

    TransformComponent(int tP_x, int tP_y, int pos_x, int pos_y, int w, int h, int sc, int sp)
    {
        texPos_x = tP_x;
        texPos_y = tP_y;
        position_x = pos_x;
        position_y = pos_y;
        width = w;
        height = h;
        scale = sc;
        speed = sp;
        
        velocity_x = velocity_y = 0;
    }

    TransformComponent(int pos_x, int pos_y, int w, int h)
    {
        position_x = pos_x;
        position_y = pos_y;
        width = w;
        height = h;
    }

    void update() override
    {
        position_x += static_cast<int>(velocity_x * speed);
        position_y += static_cast<int>(velocity_y * speed);
    }

private:
};