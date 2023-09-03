#pragma once

#include "ECS.hpp"
#include "SpriteComponent.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "../Game.hpp"
#include "../TextureManager.hpp"
#include <map>

class ToolComponent : public Component
{
public:
    SpriteComponent* sprite;

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

    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Texture *textTex;
    SDL_Rect textRect;
    SDL_Color textColor = {27, 27, 27, 160};
    TTF_Font *font;
    std::string text = "Unequipped";

    ToolComponent()
    {
        // Toolbox pos 
        tWidth = 64;
        tHeight = 64;
        box = 2;
        scale = 3;

        // Tool render initialization
        width = height = 16;
        tex = TextureManager::LoadTexture("game/assets/Objects/Items/tools and meterials.png");
        ToolInfo hoe = { x: width*2, y: height*0, tex: tex};
        ToolInfo axe = { x: width*1, y: height*0, tex: tex};
        ToolMap.emplace(1, hoe);
        ToolMap.emplace(2, axe);
        ItemMap.emplace("Hoe", 1);
        ItemMap.emplace("Axe", 2);

        // Text
        font = TTF_OpenFont("game/assets/Font/UniversCondensed.ttf", 20);
    }
    ~ToolComponent() {};

    void RenderToolbox()
    {
        SDL_SetRenderDrawColor(Game::renderer, 30, 30, 30, 100);
        for (int i = 0; i < box; i++)
        {
            SDL_RenderFillRect(Game::renderer, &bracket[i]);
        }
    }

    void RenderText()
    {
        surface = TTF_RenderText_Blended(font, text.c_str(), textColor);
        textTex = SDL_CreateTextureFromSurface(Game::renderer, surface);
        SDL_FreeSurface(surface);
        textRect.x = bracket[0].x + (tWidth / 2);
        textRect.y = 1;
        textRect.w = 40;
        textRect.h = 40;
        SDL_QueryTexture(textTex, nullptr, nullptr, &textRect.w, &textRect.h);
        SDL_RenderCopy(Game::renderer, textTex, NULL, &textRect);        
    }

    void RenderUpdateToolbox(std::string item)
    {
        int pos = ItemMap[item];
        SDL_Rect usedBracket = {bracket[pos-1].x, bracket[pos-1].y, bracket[pos-1].w, bracket[pos-1].h};
        SDL_SetRenderDrawColor(Game::renderer, 233, 236, 107, 100);
        SDL_RenderFillRect(Game::renderer, &usedBracket);
    }

    void UpdateText(std::string newText)
    {
        text = newText;
    }

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