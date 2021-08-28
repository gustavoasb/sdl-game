#include "Sprite.h"
#include "Game.h"
#include <iostream>

Sprite::Sprite(){
  this->texture = nullptr;
}

Sprite::Sprite(string file){
  this->texture = nullptr;
  Open(file);
}

Sprite::~Sprite(){
  if(this->texture != nullptr){
    SDL_DestroyTexture(this->texture);
  }
}

void Sprite::Open(string file){
  if(this->texture != nullptr){
    SDL_DestroyTexture(this->texture);
  }
  this->texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
  if(this->texture == nullptr){
    cout << "Falha ao iniciar textura de sprint" << endl;
    cout << SDL_GetError() << endl;
    exit(1);
  };
  SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
  SetClip(0, 0, this->width, this->height);
}

void Sprite::SetClip(int x, int y, int w, int h){
  this->clipRect.x = x;
  this->clipRect.y = y;
  this->clipRect.w = w;
  this->clipRect.h = h;
}

void Sprite::Render(int x, int y){
  SDL_Rect dstrect;
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = this->clipRect.w;
  dstrect.h = this->clipRect.h;
  SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &this->clipRect, &dstrect);
}

int Sprite::GetWidth(){
  return this->width;
}

int Sprite::GetHeight(){
  return this->height;
}

bool Sprite::IsOpen(){
  if(this->texture != nullptr){
    return true;
  }
  return false;
}