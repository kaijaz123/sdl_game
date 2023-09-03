#include "Game.hpp"
#include "Map.hpp"
#include "Collision.hpp"
#include "ECS/ECS.hpp"
#include "ECS/SpriteComponent.hpp"
#include "ECS/TransformComponent.hpp"
#include "ECS/ToolComponent.hpp"
#include "ECS/InputController.hpp"
#include "ECS/ColliderComponent.hpp"

// Game initialization
bool Game::isRunning = false;
SDL_Event Game::event;
SDL_Renderer* Game::renderer;
SDL_Rect Game::camera = {0, 0, 800, 640};
Manager manager;
Map *map;
Collision collider;

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
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        isRunning = true;
    }

	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}

    // Render the map
    map = new Map(3);
    map->DrawMap("game/assets/Map/layer1.map");
    map->DrawMap("game/assets/Map/layer2.map");

    player.addComponent<TransformComponent>(0, 0, 800, 640, 16, 16, 3, 3);
    player.addComponent<SpriteComponent>("game/assets/Characters/CharSheet_modified.png", 
                                         "game/assets/Characters/Character_action.png", true, 100);
    player.addComponent<ColliderComponent>(48, 48);
    player.addComponent<InputController>();
    player.addComponent<ToolComponent>();
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

auto& players(manager.getGroup(Game::groupPlayer));
auto& grounds(manager.getGroup(Game::groupMapGround));
auto& objects(manager.getGroup(Game::groupMapObject));

void Game::update()
{

    SDL_Rect playerPol, playerCol;
    std::tuple<bool, bool, bool> colCheck;
    playerPol.x = player.getComponent<TransformComponent>().position_x;
    playerPol.y = player.getComponent<TransformComponent>().position_y;
    playerCol = player.getComponent<ColliderComponent>().collider;

    manager.refresh();
    manager.update();

    // Collision check
    for (auto object : objects)
    {
        colCheck = collider.Collide(playerCol,
                                    object->getComponent<ColliderComponent>().collider);

        if (std::get<0>(colCheck))
        {
            player.getComponent<TransformComponent>().position_x = playerPol.x; 
            player.getComponent<TransformComponent>().position_y = playerPol.y; 
        }
    }
    
    camera.x = player.getComponent<TransformComponent>().position_x - 400;
    camera.y = player.getComponent<TransformComponent>().position_y - 320;

    if (camera.x <= 0)
        { camera.x = 0; }
    if (camera.y <= 0)
        { camera.y = 0; }
    if (camera.x >= Map::mapPosEdgeX - 800)
        { camera.x = Map::mapPosEdgeX - 800; }
    if (camera.y >= Map::mapPosEdgeY - 640)
        { camera.y = Map::mapPosEdgeY - 640; }
}

void Game::render()
{
    SDL_RenderClear(renderer);

    for (auto& g : grounds)
    {
        g->draw();
    }

    for (auto& o : objects)
    {
        o->draw();
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

