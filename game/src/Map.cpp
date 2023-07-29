#include "Map.hpp"
#include "TextureManager.hpp"
#include "ECS/ECS.hpp"
#include "ECS/TileComponent.hpp"
#include "Game.hpp"
extern Manager manager;

Map::Map(int mS) : mapScale(mS)
{
    grass = TextureManager::LoadTexture("game/assets/Tilesets/ground_tiles/Old_tiles/Grass.png");
    water = TextureManager::LoadTexture("game/assets/Tilesets/ground_tiles/Water.png");
}

Map::~Map()
{}

void Map::DrawMap(const char* fileMap)
{
    char c, tileType;
    int texPos_x, texPos_y;

    std::fstream mapFile;
    mapFile.open(fileMap);

    // Load Layer 0 -> All Water
    for (int i=0; i<mapSizeY; i++)
    {
        for (int j=0; j<mapSizeX; j++)
        {
            addTile(water, 0, 0, j, i, 64, 16);       
        }
    }

    // Load Layer 1 -> All submap
    for (int i=0; i<mapSizeY; i++)
    {
        for (int j=0; j<mapSizeX; j++)
        {
            mapFile.get(tileType);
            mapFile.get(c);
            texPos_x = atoi(&c);;
            mapFile.get(c);
            texPos_y = atoi(&c);

            switch (tileType)
            {
                case 'S':
                    break;

                case 'G':
                    addTile(grass, texPos_x, texPos_y, j, i, 16, 16);
                    break;

                case 'A':
                    addTile(water, texPos_x, texPos_y, j, i, 64, 16);
                    break;
                
                default:
                    break;
            }
            mapFile.ignore();
        }
    }
    mapFile.close();
}

void Map::addTile(SDL_Texture* tex, int texPos_x, int texPos_y, int pos_x, int pos_y, int tileWidth, int tileHeight)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(tex, texPos_x, texPos_y, pos_x, pos_y, tileWidth, tileHeight, mapScale);
    tile.addGroup(Game::groupMap);
}