#include "ItemComponent.hpp"

void ItemComponent::RenderToolbox()
{
    SDL_SetRenderDrawColor(Game::renderer, 30, 30, 30, 100);
    for (int i = 0; i < box; i++)
    {
        SDL_RenderFillRect(Game::renderer, &bracket[i]);
    }
}

void ItemComponent::RenderText()
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

void ItemComponent::RenderUpdateToolbox(std::string item)
{
    int pos = ItemMap[item];
    SDL_Rect usedBracket = {bracket[pos-1].x, bracket[pos-1].y, bracket[pos-1].w, bracket[pos-1].h};
    SDL_SetRenderDrawColor(Game::renderer, 233, 236, 107, 100);
    SDL_RenderFillRect(Game::renderer, &usedBracket);
}

void ItemComponent::UpdateText(std::string newText)
{
    text = newText;
}