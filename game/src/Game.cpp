#include "Game.hpp"
#include "Map.hpp"
#include "ECS/ECS.hpp"
#include "ECS/SpriteComponent.hpp"
#include "ECS/TransformComponent.hpp"
#include "ECS/InputController.hpp"

// Game initialization
bool Game::isRunning = false;
SDL_Event Game::event;
SDL_Renderer* Game::renderer;
SDL_Rect Game::camera = {0, 0, 800, 640};
Manager manager;
Map *map;

// ECS Implementation
auto& player(manager.addEntity());

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        isRunning = true;
    }

    // Render the map
    map = new Map(3);
    map->DrawMap("game/assets/Map/layer1.map");

    // player.addComponent<TransformComponent>(0, 0, 400, 320, 48, 3, 1, -90, -70);
    player.addComponent<TransformComponent>(0, 0, 800, 640, 48, 2, 3, 0, 0);
    player.addComponent<SpriteComponent>("game/assets/Characters/CharSheet.png");
    player.addComponent<InputController>();
    player.addGroup(Game::groupPlayer);
}

void Game::handleEvents()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayer));

void Game::update()
{
    manager.refresh();
    manager.update();

    camera.x = player.getComponent<TransformComponent>().position_x - 400;
    camera.y = player.getComponent<TransformComponent>().position_y - 320;

}

void Game::render()
{
    SDL_RenderClear(renderer);

    for (auto& t : tiles)
    {
        t->draw();
    }

    for (auto& p : players)
    {
        p->draw();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);    
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game closed successfully!" << std::endl;
}

