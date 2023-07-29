#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class Game
{
public:
    Game();
    ~Game();

    static bool isRunning;
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static SDL_Rect camera;

    void init(const char* title, int width, int height, bool fullscreen);
    void render();
    void update();
    void handleEvents();
    void clean();

    enum GroupLabels : std::size_t
    {
        groupMap,
        groupPlayer
    };

private:
    SDL_Window *window;
};