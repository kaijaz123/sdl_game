#include "TextureManager.hpp"
#include "Game.hpp"

TextureManager::TextureManager()
{}

TextureManager::~TextureManager()
{}

SDL_Texture* TextureManager::LoadTexture(const char* image)
{
    SDL_Surface* tempSurface = IMG_Load(image);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    return texture;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}