#include "Sprite.h"
#include <iostream>
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

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
  if(IMG_LoadTexture(renderer, file.c_str()) == nullptr){
    cout << "Falha ao iniciar janela" << endl;
    cout << SDL_GetError() << endl;
    exit(1);
  };
  SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
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
  SDL_RenderCopy(renderer, this->texture, this->clipRect, );
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