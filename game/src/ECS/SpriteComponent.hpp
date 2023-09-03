#pragma once

#include "ECS.hpp"
#include "../TextureManager.hpp"
#include "TransformComponent.hpp"
#include <SDL.h>

class SpriteComponent : public Component
{
public:
    TransformComponent *transform;
    SDL_Texture* tex;
    SDL_Rect src, dest;

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

        src.x = transform->texPos_x * transform->width;
        src.y = transform->texPos_y * transform->height;
        src.w = transform->width;
        src.h = transform->height;
    }

    void update() override
    {
        dest.x = transform->position_x - Game::camera.x;
        dest.y = transform->position_y - Game::camera.y;
        dest.w = (transform->width * transform->scale);
        dest.h = (transform->height * transform->scale);
    }

private:
};