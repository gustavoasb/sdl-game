#include "Sprite.h"
#include "Game.h"
#include "GameObject.h"
#include <iostream>

Sprite::Sprite(GameObject& associated) : Component(associated){
  this->texture = nullptr;
}

Sprite::Sprite(GameObject& associated, string file) : Component(associated){
  this->texture = nullptr;
  this->Open(file);
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
  this->SetClip(0, 0, this->width, this->height);
}

void Sprite::SetClip(int x, int y, int w, int h){
  this->clipRect.x = x;
  this->clipRect.y = y;
  this->clipRect.w = w;
  this->clipRect.h = h;
}

void Sprite::Render(){
  SDL_Rect dstrect;
  dstrect.x = this->associated.box.x;
  dstrect.y = this->associated.box.y;
  // dstrect.y = ;
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

void Sprite::Update(float dt){}

bool Sprite::Is(string type){
  if(type == "Sprite"){
    return true;
  }
  return false;
}