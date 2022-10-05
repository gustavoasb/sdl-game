#include "Sprite.h"
#include "Game.h"
#include "GameObject.h"
#include "Resources.h"
#include "Camera.h"
#include <iostream>

Sprite::Sprite(GameObject& associated) : Component(associated){
  SetScaleX(Vec2(1.0, 1.0));
  this->texture = nullptr;
}

Sprite::Sprite(GameObject& associated, string file, int frameCount, float frameTime) : Component(associated) {
  SetScaleX(Vec2(1.0, 1.0));
  this->texture = nullptr;
  this->SetFrameCount(frameCount);
  this->Open(file);
  this->setFrameTime(frameTime);
  this->currentFrame = 0;
  this->timeElapsed = 0;
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

  this->width = this->width / this->frameCount;

  associated.box.w = this->width;
  associated.box.h = this->height;

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
  dstrect.w = this->clipRect.w * scale.x;
  dstrect.h = this->clipRect.h * scale.y;
  SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), this->texture, &clipRect, &dstrect, 
    associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

void Sprite::Render(){
   Render(this->associated.box.x - Camera::pos.x, this->associated.box.y - Camera::pos.y);
}

int Sprite::GetWidth(){
  return this->width * scale.x;
}

int Sprite::GetHeight(){
  return this->height * scale.y;
}

bool Sprite::IsOpen(){
  if(this->texture != nullptr){
    return true;
  }
  return false;
}

void Sprite::Update(float dt){
  timeElapsed += dt;
  int nextFrame = (int)(timeElapsed / frameTime) % frameCount;
  
  if (nextFrame != this->currentFrame) SetFrame(nextFrame);
}

void Sprite::SetFrame(int frame){
  this->currentFrame = frame;
  SetClip(this->width * currentFrame, 0, this->width, this->height);
}

void Sprite::SetFrameCount(int frameCount){
  this->frameCount = frameCount;
  associated.box.w = (float)this->width/frameCount;
  this->currentFrame = 0;
}

void Sprite::setFrameTime(float frameTime){
  this->frameTime = frameTime;
}

bool Sprite::Is(string type){
  if(type == "Sprite"){
    return true;
  }
  return false;
}

void Sprite::Start(){}

void Sprite::SetScaleX(Vec2 scale){ 
  if(scale.x == 0) scale.x = this->scale.x;
  if(scale.y == 0) scale.y = this->scale.y;
  this->scale = scale;
}

Vec2 Sprite::GetScale(){ 
  return scale; 
}