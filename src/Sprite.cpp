#include "Sprite.h"
#include "Game.h"
#include "GameObject.h"
#include "Resources.h"
#include <iostream>

Sprite::Sprite(GameObject& associated) : Component(associated){
  this->texture = nullptr;
}

Sprite::Sprite(GameObject& associated, string file) : Component(associated){
  this->texture = nullptr;
  this->Open(file);
}

Sprite::~Sprite(){
  this->texture = nullptr;
}

void Sprite::Open(string file){
  if(this->texture != nullptr){
    texture = Resources::GetImage(file);
  }
  this->texture = Resources::GetImage(file);

  SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
  this->SetClip(0, 0, this->width, this->height);
}

void Sprite::SetClip(int x, int y, int w, int h){
  this->clipRect.x = x;
  this->clipRect.y = y;
  this->clipRect.w = w;
  this->clipRect.h = h;
}

void Sprite::Render(float x, float y){
  SDL_Rect dstrect;
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = this->clipRect.w;
  dstrect.h = this->clipRect.h;
  SDL_RenderCopy(Game::GetInstance().GetRenderer(), this->texture, &this->clipRect, &dstrect);
}

void Sprite::Render(){
   Render(this->associated.box.x, this->associated.box.y);
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