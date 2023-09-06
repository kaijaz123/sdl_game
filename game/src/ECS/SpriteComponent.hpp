#pragma once

#include "ECS.hpp"
#include "../TextureManager.hpp"
#include "TransformComponent.hpp"
#include "Animation.hpp"
#include <SDL2/SDL.h>
#include <map>

class SpriteComponent : public Component
{
public:
    TransformComponent *transform;
    SDL_Texture* tex;
    SDL_Texture* tex_mve;
    SDL_Texture* tex_act;
    SDL_Rect src, dest;

    // animation
    bool animated;
    int speed, frames;
    int y_index = 0;
    int i_index;
    int pos;
    std::map<std::string, Animation> AniMap; 
    std::string current_move = "Idle";

    // action
    struct
    {
        std::string name = "";
        bool onHold = false; 
    } action;
    int move = 0;

    SpriteComponent() = default;
    ~SpriteComponent() {};

    SpriteComponent(const char* file, const char* file_action, bool ani, int s)
    {
        tex_mve = TextureManager::LoadTexture(file);
        Animation Idle = Animation(4, s, tex_mve, 16, 16);
        AniMap.emplace("Idle", Idle);

        tex_act = TextureManager::LoadTexture(file_action);
        Animation Action = Animation(8, s, tex_act, 16, 48);
        AniMap.emplace("Action", Action);
        
        animated = ani;
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        src.x = src.y = 0;
        src.w = transform->width;
        src.h = transform->height;
    }

    void update() override
    {
        if (animated)
        {
            // Render info
            tex = AniMap[current_move].tex;
            src.w = AniMap[current_move].width;
            src.h = transform->height = AniMap[current_move].height;
            speed = AniMap[current_move].speed;
            frames = AniMap[current_move].frames;

            if (current_move == "Idle")
            {
                // Render idle and udlr move
                i_index = static_cast<int>(((SDL_GetTicks() / speed) % frames));
                pos = i_index + (i_index * 2);
                src.x = src.w * pos;
                src.y = src.h * (y_index + y_index * 2);

                // dest pos
                dest.y = transform->position_y - Game::camera.y;
            }
            else if (action.onHold == true && current_move == "Action")
            { 
                // Render basic action move
                i_index = static_cast<int>(((SDL_GetTicks() / speed) % frames));
                pos = i_index + (i_index * 2) + 1;
                src.x = src.w * pos;
                src.y = src.h * y_index;

                // dest pos
                dest.y = transform->position_y - Game::camera.y - 72;
            }
        }

        dest.x = transform->position_x - Game::camera.x;
        dest.w = (transform->width * transform->scale);
        dest.h = (transform->height * transform->scale);
    }

    void draw() override
    {
        TextureManager::Draw(tex, src, dest, SDL_FLIP_NONE);
    }

    void Play(std::string mName)
    {
        current_move = mName;
    }

private:
};