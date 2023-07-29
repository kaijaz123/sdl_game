#pragma once

#include <SDL.h>
#include <iostream>
#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "../Game.hpp"

class InputController : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    InputController() = default;
    ~InputController() {}

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    {
        if (Game::event.type == SDL_KEYDOWN)
        {       
            if (Game::event.key.keysym.sym == SDLK_w)
                { transform->velocity_y = -1;}
            
            else if (Game::event.key.keysym.sym == SDLK_s)
                { transform->velocity_y = 1;}
            
            else if (Game::event.key.keysym.sym == SDLK_a)
                { transform->velocity_x = -1;}
            
            else if (Game::event.key.keysym.sym == SDLK_d)
                { transform->velocity_x = 1;}
        }

        if (Game::event.type == SDL_KEYUP)
        {
             if (Game::event.key.keysym.sym == SDLK_w)
                { transform->velocity_y = 0;}
            
            else if (Game::event.key.keysym.sym == SDLK_s)
                { transform->velocity_y = 0;}
            
            else if (Game::event.key.keysym.sym == SDLK_a)
                { transform->velocity_x = 0;}
            
            else if (Game::event.key.keysym.sym == SDLK_d)
                { transform->velocity_x = 0;}           
        }

    }
};