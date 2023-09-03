#pragma once

// #include "Components.hpp"
#include "SpriteComponent.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "../Game.hpp"
#include "../TextureManager.hpp"
#include <map>

class ItemComponent : public Component
{
public:
    // Tool and Item
    int box;
    int tWidth, tHeight;
    int width , height;
    int scale;

    struct ToolInfo
    {
        int x;
        int y;
        SDL_Texture* tex;
    };
    
    std::map<int, ToolInfo> ToolMap;
    std::map<std::string, int> ItemMap;
    SDL_Rect bracket[2], src, dest;
    SDL_Texture *tex;

    // Font
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Texture *textTex;
    SDL_Rect textRect;
    SDL_Color textColor = {27, 27, 27, 200};
    TTF_Font *font;
    std::string text = "Unequipped";
    SpriteComponent* sprite;
    

    ItemComponent() = default;
    ItemComponent(std::string iTex, std::string fontTex)
    {
        // Toolbox pos 
        tWidth = 64;
        tHeight = 64;
        box = 2;
        scale = 3;

        // Tool render initialization
        width = height = 16;
        tex = TextureManager::LoadTexture(iTex.c_str());
        ToolInfo hoe = { x: width*2, y: height*0, tex: tex};
        ToolInfo axe = { x: width*1, y: height*0, tex: tex};
        ToolMap.emplace(1, hoe);
        ToolMap.emplace(2, axe);
        ItemMap.emplace("Hoe", 1);
        ItemMap.emplace("Axe", 2);

        // Text
        font = TTF_OpenFont(fontTex.c_str(), 20);
    }
    ~ItemComponent() {};

    void RenderToolbox();
    void RenderText();
    void RenderUpdateToolbox(std::string item);
    void UpdateText(std::string newText);

    void init() override
    {
        // Toolbox pos
        for (int i = 0; i < box; i++)
        {
            bracket[i].x = tWidth * (i+1) + (i * 10);
            bracket[i].y = 25;
            bracket[i].w = tWidth;
            bracket[i].h = tHeight;
        }
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void draw() override
    {
        RenderText();
        RenderToolbox();
        if (sprite->action.onHold)
        { RenderUpdateToolbox(sprite->action.name); }

        for (int i = 0; i < box; i++)
        {
            src.x = ToolMap[i+1].x;
            src.y = ToolMap[i+1].y;
            src.w = width;
            src.h = height;
            tex = ToolMap[i+1].tex;

            dest.x = bracket[i].x + 10;
            dest.y = bracket[i].y + 10;
            dest.w = width * scale;
            dest.h = height * scale;
            TextureManager::Draw(tex, src, dest, SDL_FLIP_NONE);
        }
    }
    
private:
};