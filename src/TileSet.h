#ifndef _TILE_SET_H
#define _TILE_SET_H

#include <string>
#include "Sprite.h"
using namespace std;

class TileSet {
  public:
    TileSet(int tileWidth, int tileHeight, std::string file);
    ~TileSet();
    void RenderTile(unsigned int index, float x, float y);
    int GetTileWidth();
    int GetTileHeight();
  private:
    Sprite tileSet;
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;
};

#endif