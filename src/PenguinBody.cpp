#include "PenguinBody.h"
#include "Sprite.h"
#include "PenguinCannon.h"
#include "InputManager.h"
#include "Game.h"
#include "Camera.h"
#include "Bullet.h"
#include "Collider.h"
#include <iostream>
#define PI 3.14159265358979323846

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated){

  Sprite *sprite = new Sprite(associated, "./assets/img/penguin.png");
  associated.AddComponent(sprite);

  Collider *col = new Collider(associated);
  associated.AddComponent(col);

  PenguinBody::player = this;

  this->angle = 0;
  this->hp = 20;
  this->linearSpeed = 5;
  this->speed = Vec2(1.0, 1.0);
}

PenguinBody::~PenguinBody(){
  PenguinBody::player = nullptr;
}

void PenguinBody::Start(){
  GameObject *cannonObj = new GameObject();
  PenguinCannon *cannon = new PenguinCannon(*cannonObj, Game::GetInstance().GetState().GetObjectPtr(&associated));
  cannonObj->AddComponent(cannon);
  this->pcannon = Game::GetInstance().GetState().AddObject(cannonObj);
}

void PenguinBody::Update(float dt){
  if(!hp){
    Camera::Unfollow();
    associated.RequestDelete();
    pcannon.lock()->RequestDelete();

    GameObject *go = new GameObject();
    go->box.x = associated.box.x;
    go->box.y = associated.box.y;
    go->AddComponent(new Sprite(*go, "assets/img/penguindeath.png", 5, 0.1, 0.4));

    Game::GetInstance().GetState().AddObject(go);

    return;
  }

  InputManager &input = InputManager::GetInstance();
  if(input.IsKeyDown(SDLK_a)) {
    angle -= 4 * dt;
  }
  if(input.IsKeyDown(SDLK_d)) {
    angle += 4 * dt;
  }
  if(input.IsKeyDown(SDLK_w)) {
    linearSpeed += 10;
  }
  if(input.IsKeyDown(SDLK_s)) {
    linearSpeed -= 10;
  }

  this->speed = Vec2(linearSpeed, linearSpeed).GetRotated(angle - PI / 4);

  associated.angleDeg = angle * 180 / PI;
  associated.box.x += speed.x * dt;
  associated.box.y += speed.y * dt;
}

void PenguinBody::Render(){}

bool PenguinBody::Is(std::string type){
  if(type == "PenguinBody"){
    return true;
  }
  return false;
}

Vec2 PenguinBody::GetCenter(){ 
  return associated.box.GetCenter(); 
}

void PenguinBody::NotifyCollision(GameObject &other) {
  if (other.GetComponent("Bullet") != nullptr) {
    Bullet *bullet = (Bullet *)other.GetComponent("Bullet");
    if (bullet->targetsPlayer) {
      hp -= bullet->GetDamage();
    }
  }
}
