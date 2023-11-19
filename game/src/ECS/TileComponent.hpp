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
    bool tile;

    TileComponent() = default;
    ~TileComponent() {};

    TileComponent(SDL_Texture* texture, int texPos_x, int texPos_y, int pos_x, int pos_y, 
                  int tileWidth, int tileHeight, int scale, bool tex8, bool tile)
    {
        tex = texture;
        this->tile = tile;

        src.x = texPos_x * tex8_Process(tex8, tileWidth);
        src.y = texPos_y * tex8_Process(tex8, tileHeight);
        src.w = tileWidth;
        src.h = tileHeight;

        dest.w = tileWidth * scale;
        dest.h = tileHeight * scale;

        position_x = pos_x * (tileWidth * scale);
        position_y = pos_y * (tileHeight * scale);
    }

    int tex8_Process(bool tex8, int tileSize)
    {
        if (tex8)
        { return tileSize/2; }

        return tileSize;
    }

    void draw() override
    {
        if (tile) TextureManager::Draw(tex, src, dest, SDL_FLIP_NONE);
    }

    void update() override
    {
        dest.x = position_x - Game::camera.x;
        dest.y = position_y - Game::camera.y;
    }
};
