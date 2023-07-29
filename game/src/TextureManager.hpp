#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();
    
    static SDL_Texture* LoadTexture(const char* image);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};