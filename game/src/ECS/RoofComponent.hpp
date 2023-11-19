#include "ECS.hpp"
#include "TileComponent.hpp"
// #include "DoorComponent.hpp"

#include "../TextureManager.hpp"
#include "../Game.hpp"

class RoofComponent : public Component
{
public:
    RoofComponent() = default;
    ~RoofComponent() {};

    TileComponent* tile;
    int alpha = 255;
    bool transparent = false;

    void init() override
    {
        tile = &entity->getComponent<TileComponent>();
    }

    void update() override
    {
        auto& objects(manager.getGroup(Game::groupMapObject));
        // Get door status
        for (auto& object : objects)
        {
            bool doorFound = object->hasComponent<DoorComponent>();
            if (doorFound && object->getComponent<DoorComponent>().open && alpha > 0)
            {
                alpha -= 3;
            }

            if (doorFound && !object->getComponent<DoorComponent>().open && alpha < 255)
            {
                alpha += 3;
            }
        }
    }

    void draw() override
    {
        TextureManager::Draw(tile->tex, tile->src, tile->dest, SDL_FLIP_NONE, alpha);   
    }

};