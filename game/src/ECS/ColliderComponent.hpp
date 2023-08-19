#pragma once

#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "TileComponent.hpp"
#include <SDL2/SDL.h>
#include "../Game.hpp"

class ColliderComponent : public Component
{
public:
    TransformComponent *transform;
    TileComponent *tile;
    SDL_Rect collider;
    int width, height;
    bool object = false;

    ColliderComponent() = default;
    ~ColliderComponent() {};

    ColliderComponent(int w, int h)
    {
        width = w;
        height = h;
    }

    ColliderComponent(bool obj)
    {
        object = obj;
    }

    void update() override
    {
        if (object)
            { collider.x = tile->position_x;
              collider.y = tile->position_y; 
              collider.w = tile->dest.w;
              collider.h = tile->dest.h; }
        else
            { collider.x = transform->position_x;
              collider.y = transform->position_y; 
              collider.w = transform->width * transform->scale;
              collider.h = transform->height * transform->scale;}
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        tile = &entity->getComponent<TileComponent>();
    }
};