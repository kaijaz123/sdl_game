#include <iostream>
#include "Game.hpp"

int WinMain()
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    int frameTime;
    Uint32 frameStart;

    // Game initialization
    Game *game = new Game();
    game->init("Game", 800, 640, false);

    while (Game::isRunning == true)
    {
        // To capture the framerate to 60FPS
        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();
    return 0;
}