#include "Map.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
#include "ECS/TileComponent.hpp"
#include "ECS/TransformComponent.hpp"
#include "ECS/ColliderComponent.hpp"
#include "ECS/DoorComponent.hpp"
#include "ECS/RoofComponent.hpp"

extern Manager manager;
int Map::mapPosEdgeX = 0;
int Map::mapPosEdgeY = 0;

Map::Map(int mS) : mapScale(mS)
{
    grass = TextureManager::LoadTexture("game/assets/Tilesets/ground_tiles/Old_tiles/Grass.png");
    water = TextureManager::LoadTexture("game/assets/Tilesets/ground_tiles/Water.png");
    house = TextureManager::LoadTexture("game/assets/Tilesets/building_parts/WoodenHouse.png");
    door = TextureManager::LoadTexture("game/assets/Tilesets/building_parts/Door.png");
    tree = TextureManager::LoadTexture("game/assets/Objects/Tree/tree_sprites.png");
    dirt = TextureManager::LoadTexture("game/assets/Tilesets/ground_tiles/Old_tiles/Tilled Dirt.png");
    farmPlant = TextureManager::LoadTexture("game/assets/Objects/Farming Plants.png");
    wood = TextureManager::LoadTexture("game/assets/Objects/Trees, stumps and bushes.png");
    mfs = TextureManager::LoadTexture("game/assets/Objects/Mushrooms, Flowers, Stones.png");

    // Load Layer 0 -> All Water
    for (int y=0; y<mapSizeY; y++)
    {
        for (int x=0; x<mapSizeX; x++)
        {
            addTile(water, 0, 0, x, y, 64, 16);
            // Store the position of the edge of map
            if (x == mapSizeX-1)
                { mapPosEdgeX = 64 * mapScale * (x+1); }
            
            if ( y == mapSizeY-1)
                { mapPosEdgeY = 16 * mapScale * (y+1); }
        }
    }
}

Map::~Map()
{}

Map::RenderStructure Map::extractInfo(std::fstream& file)
{
    Map::RenderStructure tileInfo;
    char tileType, c;
    int texPos_x, texPos_y;

    file.get(tileType);
    tileInfo.tileType = tileType;

    file.get(c);
    texPos_x = atoi(&c);
    tileInfo.texPos_x = texPos_x;

    file.get(c);
    texPos_y = atoi(&c);
    tileInfo.texPos_y = texPos_y;

    return tileInfo;
}

void Map::checkTile(Map::RenderStructure tileSet, int x, int y)
{
    switch (tileSet.tileType)
    {
        case 'S':
            break;
        
        case 'C':
            addTile(water, tileSet.texPos_x, tileSet.texPos_x, x, y, 16, 16, false, true);
            break;

        case 'G':
            addTile(grass, tileSet.texPos_x, tileSet.texPos_y, x, y, 16, 16);
            break;
        
        case 'D':
            doorEnt = &addTile(door, tileSet.texPos_x, tileSet.texPos_y, x, y, 16, 16, false, true, false);
            doorEnt->addComponent<DoorComponent>();
            break;
        
        case 'R': // For roof
            roofEnt = &addTile(house, tileSet.texPos_x, tileSet.texPos_y, x, y, 16, 16, true, true, false);
            roofEnt->addComponent<RoofComponent>();
            break;
        
        case 'H':
            addTile(house, tileSet.texPos_x, tileSet.texPos_y, x, y, 16, 16, true, true);
            break;

        case 'T':
            addTile(tree, tileSet.texPos_x, tileSet.texPos_y, x, y, 16, 16, true, true);
            break;
        
        case 'I':
            addTile(dirt, tileSet.texPos_x, tileSet.texPos_y, x, y, 16, 16, true, false);
            break;
        
        case 'P':
            addTile(farmPlant, tileSet.texPos_x, tileSet.texPos_y, x, y, 16, 16);
            break;
        
        case 'B':
            addTile(wood, tileSet.texPos_x, tileSet.texPos_y, x, y, 16, 16);
            break;
        
        case 'M':
            addTile(mfs, tileSet.texPos_x, tileSet.texPos_y, x, y, 16, 16);
            break;
        
        default:
            break;
    }
}

void Map::DrawMap(const char* fileMap)
{
    Map::RenderStructure tileSet;
    Map::RenderStructure objectSet;

    std::fstream mapFile;
    mapFile.open(fileMap);

    for (int y=0; y<mapSizeY; y++)
    {
        for (int x=0; x<mapSizeX; x++)
        {
            while (true)
            {
                tileSet = extractInfo(mapFile);
                checkTile(tileSet, x, y);
                    
                char nextChar = mapFile.peek();
                if (!std::isalpha(nextChar))
                    { break; }
            }
            mapFile.ignore();
        }
    }
    mapFile.close();
}

Entity& Map::addTile(SDL_Texture* tex, int texPos_x, int texPos_y, int pos_x, int pos_y, int tileWidth, 
                  int tileHeight, bool tex8, bool obj, bool tile, Entity* entity)
{
    if (!obj)
    {
        auto& ground(manager.addEntity());
        ground.addComponent<TileComponent>(tex, texPos_x, texPos_y, pos_x, pos_y, tileWidth, tileHeight, mapScale, tex8, tile);
        ground.addGroup(Game::groupMapGround);

        return ground;
    }

    else
    {
        auto& object(manager.addEntity());

        object.addComponent<TransformComponent>();
        object.addComponent<ColliderComponent>(true);
        object.addComponent<TileComponent>(tex, texPos_x, texPos_y, pos_x, pos_y, tileWidth, tileHeight, mapScale, tex8, tile);

        object.addGroup(Game::groupMapObject);

        return object;
    }
}