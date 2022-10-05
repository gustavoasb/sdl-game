#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "State.h"
#include "Game.h"
#include "Camera.h"
#include <iostream>
#define PI 3.14159265358979323846

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffset)
  : Component(associated), alienCenter(alienCenter), arc(arcOffset){

  Sprite *sprite = new Sprite(associated, "./assets/img/minion.png");
  associated.AddComponent(sprite);

  float scale = 1.0 + (1.5 - 1.0) * ((float) rand()) / (float) RAND_MAX;
  sprite->SetScaleX(Vec2(scale, scale));
}

void Minion::Update(float dt) {
  Vec2 minionPos = Vec2(130.0, 0.0).GetRotated(arc);

  std::shared_ptr<GameObject> alienObj = alienCenter.lock();
  Vec2 alienPos = Vec2(0,0);
  if(alienObj){
    alienPos = Vec2(alienObj->box.GetCenter());
  }
  Vec2 target = alienPos + minionPos;

  arc += dt * 0.4;


  this->associated.angleDeg = (associated.box.GetCenter() - alienPos).GetAngle() * 180 / PI;
  this->associated.box.x = target.x - this->associated.box.w/2.0;
  this->associated.box.y = target.y - this->associated.box.h/2.0;
}

void Minion::Shoot(Vec2 target) {
  GameObject *bullet = new GameObject();

  float angle = (target - associated.box.GetCenter()).GetAngle();
  bullet->AddComponent(new Bullet(*bullet, angle, 500, 1, 1000, "./assets/img/minionbullet2.png"));
  bullet->box.x = this->associated.box.x - bullet->box.w / 2.0;
  bullet->box.y = this->associated.box.y - bullet->box.h / 2.0;

  Game::GetInstance().GetState().AddObject(bullet);
}

void Minion::Render(){}

bool Minion::Is(std::string type){
  if(type == "Minion"){
    return true;
  }
  return false; 
}