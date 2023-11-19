#include "ECS.hpp"
#include "TileComponent.hpp"
#include "TransformComponent.hpp"
#include "ColliderComponent.hpp"
#include "SpriteComponent.hpp"

#include "../Game.hpp"
#include "../TextureManager.hpp"

#include <SDL.h>
#include <algorithm>

extern Manager manager;

class DoorComponent : public Component
{
public:
    DoorComponent() = default;
    ~DoorComponent() {};

    TileComponent* tile;
    ColliderComponent *collider;
    SpriteComponent *sprite;
    SDL_Rect playerPos;

    // Animation
    bool open = false;
    int i_index = 4;

    void init() override
    {
        tile = &entity->getComponent<TileComponent>();
        collider = &entity->getComponent<ColliderComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override
    {
        auto& players(manager.getGroup(Game::groupPlayer));

        for (Entity* player : players)
        {
            playerPos.x = player->getComponent<TransformComponent>().position_x;
            playerPos.y = player->getComponent<TransformComponent>().position_y;

            // Open animation
            if (std::abs(playerPos.x - collider->collider.x) < 10 && 
                std::abs(playerPos.y - (collider->collider.y + collider->collider.h)) < 10 &&
                !open)
            {
                if (i_index > 0)
                {
                    tile->src.x = tile->src.w * i_index;
                    i_index--;
                }
                else
                {
                    open = true;
                }
            }

            // Close animation
            if ((std::abs(playerPos.x - collider->collider.x) > 10 ||
                std::abs(playerPos.y - (collider->collider.y + collider->collider.h)) > 10) &&
                open)
            {

                if (i_index < 6)
                {
                    tile->src.x = tile->src.w * i_index;
                    i_index++;
                }
                else
                {
                    open = false;
                    i_index = 4; // reset
                }
            }
        }
    }

    void draw() override
    {

        TextureManager::Draw(tile->tex, tile->src, tile->dest, SDL_FLIP_NONE);
    }

};