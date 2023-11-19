#pragma once

#include "TransformComponent.hpp"
#include "ItemComponent.hpp"
#include "SpriteComponent.hpp"
#include <SDL.h>
#include <iostream>
#include "../Game.hpp"

class InputController : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    ItemComponent *item;

    InputController() = default;
    ~InputController() {}

    void init() override
    {
        item = &entity->getComponent<ItemComponent>();
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    {
        if (Game::event.type == SDL_KEYDOWN)
        {   
            // BASIC MOVE
            if (Game::event.key.keysym.sym == SDLK_w)
                { transform->velocity_y = -1;
                  sprite->y_index = 2;}
            
            else if (Game::event.key.keysym.sym == SDLK_s)
                { transform->velocity_y = 1;
                  sprite->y_index = 1;}
            
            else if (Game::event.key.keysym.sym == SDLK_a)
                { transform->velocity_x = -1; 
                  sprite->y_index = 3;}
            
            else if (Game::event.key.keysym.sym == SDLK_d)
                { transform->velocity_x = 1;
                  sprite->y_index = 4;}
            
            // ACTION MOVE
            else if (Game::event.key.keysym.sym == SDLK_1)
                { sprite->action.onHold = true;
                  sprite->action.name = "Hoe";
                  item->UpdateText("[Hoe] Equipped");}
            
            else if (Game::event.key.keysym.sym == SDLK_2)
                { sprite->action.onHold = true;
                  sprite->action.name = "Axe";
                  item->text = "[Axe] Equipped"; }
        }

        if (Game::event.type == SDL_KEYUP)
        {
            // BASIC MOVE
            if (Game::event.key.keysym.sym == SDLK_w)
                { transform->velocity_y = 0;}
            
            else if (Game::event.key.keysym.sym == SDLK_s)
                { transform->velocity_y = 0;}
            
            else if (Game::event.key.keysym.sym == SDLK_a)
                { transform->velocity_x = 0;}
            
            else if (Game::event.key.keysym.sym == SDLK_d)
                { transform->velocity_x = 0;}   

            
            // RELEASE ACTION MOVE
            else if (Game::event.key.keysym.sym == SDLK_ESCAPE)
                { sprite->action.onHold = false;
                  sprite->action.name = "";
                  sprite->move = 0;
                  sprite->Play("Idle"); 
                  item->text = "Unequipped"; }        
            
            sprite->y_index = 0;       
        }


        if (Game::event.type == SDL_MOUSEBUTTONDOWN)
        {
            // MOUSE MOVE && ACTION MOVE
            if (sprite->action.onHold == true && sprite->action.name == "Hoe" &&
                Game::event.button.button == SDL_BUTTON_LEFT)
                { sprite->move = 1;
                  sprite->y_index = 0;
                  sprite->Play("Action"); }

            if (sprite->action.onHold == true && sprite->action.name == "Axe" &&
                Game::event.button.button == SDL_BUTTON_LEFT)
                { sprite->move = 2;
                  sprite->y_index = 4;
                  sprite->Play("Action"); }                  
        }

        if (Game::event.type == SDL_MOUSEBUTTONUP)
        {
            // MOUSE MOVE && ACTION MOVE
            if (Game::event.button.button == SDL_BUTTON_LEFT)
                { sprite->move = 0;
                  sprite->y_index = 0; 
                  sprite->Play("Idle");}
        }

    }
};