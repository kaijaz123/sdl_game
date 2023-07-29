#pragma once

#include "ECS.hpp"
#include "../TextureManager.hpp"
#include "TransformComponent.hpp"
#include "SDL.h"

class SpriteComponent : public Component
{
public:
    TransformComponent *transform;

    SpriteComponent() = default;
    ~SpriteComponent() {};

    SpriteComponent(const char* file)
    {
        tex = TextureManager::LoadTexture(file);
    }
    
    void draw() override
    {
        TextureManager::Draw(tex, src, dest, SDL_FLIP_NONE);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        src.x = transform->texPos_x;
        src.y = transform->texPos_y;
        src.w = src.h = transform->size;
    }

    void update() override
    {
        dest.x = transform->position_x - Game::camera.x;
        dest.y = transform->position_y - Game::camera.y;
        dest.w = (transform->size * transform->scale);
        dest.h = (transform->size * transform->scale);
    }

private:
    SDL_Texture* tex;
    SDL_Rect src, dest;
};