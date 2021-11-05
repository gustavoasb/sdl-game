#include "TileSet.h"
#include "Sprite.h"
#include "GameObject.h"

TileSet::TileSet(int tileWidth, int tileHeight, string file) : tileSet(*new GameObject()){
  tileSet.Open(file);
  this->tileWidth = tileWidth;
  this->tileHeight = tileHeight;
  this->rows = tileSet.GetHeight() / tileHeight;
  this->columns = tileSet.GetWidth() / tileWidth;  
}

void TileSet::RenderTile(unsigned int index, float x, float y){
  if (index > (unsigned int)(rows * columns)) return;
  int clipX = index % columns * tileWidth, clipY = index / columns * tileHeight;
  tileSet.SetClip(clipX, clipY, tileWidth, tileHeight);
  tileSet.Render(x, y);
}

int TileSet::GetTileHeight(){
  return this->tileHeight;
}

int TileSet::GetTileWidth(){
  return this->tileWidth;
}

TileSet::~TileSet(){

}