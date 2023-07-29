#pragma once

#include "ECS.hpp"
#include "../Game.hpp"
#include <SDL.h>
#include "../TextureManager.hpp"

class TileComponent : public Component
{
public:
    SDL_Rect src, dest;
    SDL_Texture* tex;
    int position_x, position_y;

    TileComponent() = default;
    ~TileComponent() {};

    TileComponent(SDL_Texture* texture, int texPos_x, int texPos_y, int pos_x, int pos_y, 
                  int tileWidth, int tileHeight, int scale)
    {
        tex = texture;

        src.x = texPos_x * tileWidth;
        src.y = texPos_y * tileHeight;
        src.w = tileWidth;
        src.h = tileHeight;

        dest.w = tileWidth * scale;
        dest.h = tileHeight * scale;

        position_x = pos_x * (tileWidth * scale);
        position_y = pos_y * (tileHeight * scale);
    }

    void draw() override
    {
        TextureManager::Draw(tex, src, dest, SDL_FLIP_NONE);
    }

    void update() override
    {
        dest.x = position_x - Game::camera.x;
        dest.y = position_y - Game::camera.y;
    }
};
