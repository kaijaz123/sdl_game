#pragma once

#include "ECS.hpp"
#include "TransformComponent.hpp"
#include <SDL2/SDL.h>

class ColliderComponent : public Component
{
public:
    TransformComponent *transform;
    SDL_Rect collider;
    int width, height;

    ColliderComponent() = default;
    ~ColliderComponent() {};

    ColliderComponent(int w, int h)
    {
        transform = &entity->getComponent<TransformComponent>();
        width = w;
        height = h;
    }

    void update() override
    {
        collider.x = transform->position_x;
        collider.y = transform->position_y;
        collider.w = width;
        collider.h = height;
    }
};