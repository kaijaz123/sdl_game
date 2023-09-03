#include <iostream>
#include <fstream>
#include <cctype>
#include <SDL2/SDL.h>

class Map
{
public:
    // mS = mapScale, tW = tileWidth, tH = tileHeight
    Map(int mS);
    ~Map();
    // int mapPosEdgeX{0};
    // int mapPosEdgeY{0};
    static int mapPosEdgeX;
    static int mapPosEdgeY;

    struct RenderStructure{
        char tileType;
        int texPos_x;
        int texPos_y;
    };

    void DrawMap(const char* fileMap);
    void checkTile(RenderStructure tileSet, int x, int y);
    void addTile(SDL_Texture* tex, int texPos_x, int texPos_y, int pos_x, int pos_y, int tileWidth, 
                  int tileHeight, bool tex8 = false, bool obj = false); // Tileset consists of ground and object
    RenderStructure extractInfo(std::fstream& file);

private:
    // File size currently set to 25x25
    int mapSizeX = 25;
    int mapSizeY = 30;

    int mapScale;

    // Texuture
    SDL_Texture* grass;
    SDL_Texture* water;
    SDL_Texture* house;
    SDL_Texture* door;
    SDL_Texture* tree;
    SDL_Texture* dirt;
    SDL_Texture* farmPlant;
    SDL_Texture* wood;
    SDL_Texture* mfs;
};