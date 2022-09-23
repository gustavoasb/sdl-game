#include "TileMap.h"
#include "Camera.h"
#include <fstream>
#include <iostream>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet)  : Component(associated){
  this->Load(file);
  this->SetTileSet(tileSet);
}

void TileMap::Load(std::string file){
  ifstream stream(file, ios::in);

  if (!stream.is_open())
  {
    std::cout << "Error loading file " << file << std::endl;
    exit(1);
  }

  char c;

  stream >> mapWidth >> c >> mapHeight >> c >> mapDepth >> c;

  int in;
  while (stream >> in)
  {
    tileMatrix.push_back(in - 1);
    stream >> c;
  }
}

void TileMap::SetTileSet(TileSet* tileSet){
  this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z){
  int idx = z * mapWidth * mapHeight + y * mapWidth + x;
  return tileMatrix[idx];
}

void TileMap::Render(){
  // i = layer
  for (int i = 0; i < mapDepth; i++){
    RenderLayer(i, (int)Camera::pos.x*(i+1), (int)Camera::pos.y*(i+1));
  }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
  for (int y = 0; y < mapHeight; y++){
    for (int x = 0; x < mapWidth; x++){
      int xPos = x * tileSet->GetTileWidth() - cameraX;
      int yPos = y * tileSet->GetTileHeight() - cameraY;
      tileSet->RenderTile(At(x, y, layer), xPos, yPos);
    }
  }
}

int TileMap::GetWidth(){
  return this->mapWidth;
}

int TileMap::GetHeight(){
  return this->mapHeight;
}

int TileMap::GetDepth(){
  return this->mapDepth;
}

bool TileMap::Is(string type)
{
  return "TileMap" == type;
}

TileMap::~TileMap(){}

void TileMap::Update(float dt){}

void TileMap::Start(){}