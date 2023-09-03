#include <iostream>
#include <SDL2/SDL.h>

class Animation
{
public:
    int frames;
    int speed;
    int width, height;
    SDL_Texture *tex;
    SDL_Rect src, dest;

    Animation() {};
    Animation(int f, int s, SDL_Texture* t, int w, int h)
    {
        frames = f;
        speed = s;
        tex = t;
        width = w;
        height = h;
    }

    ~Animation() {};
};