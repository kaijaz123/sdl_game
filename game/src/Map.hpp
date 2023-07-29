#include <iostream>
#include <fstream>
#include <SDL.h>

class Map
{
public:
    // mS = mapScale, tW = tileWidth, tH = tileHeight
    Map(int mS);
    ~Map();

    void DrawMap(const char* fileMap);
    void addTile(SDL_Texture* tex, int texPos_x, int texPos_y, int pos_x, int pos_y, int tileWidh = 16, int tileHeight = 16);

private:
    // File size currently set to 25x25
    int mapSizeX = 25;
    int mapSizeY = 30;

    int mapScale;

    // Texuture
    SDL_Texture* grass;
    SDL_Texture* water;
};