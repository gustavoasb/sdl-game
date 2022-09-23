#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "State.h"
#include "Game.h"
#include "Camera.h"
#define PI 3.14159265358979323846

Minion::Minion(GameObject &associated, std::weak_ptr<GameObject> alienCenter, float arcOffset)
  : Component(associated), alienCenter(alienCenter), arc(arcOffset){

  Sprite *sprite = new Sprite(associated, "./assets/img/minion.png");
  associated.AddComponent(sprite);
}

void Minion::Update(float dt) {
  Vec2 minionPos = Vec2(130.0, 0.0).GetRotated(arc);
  std::shared_ptr<GameObject> alienObj = alienCenter.lock();
  Vec2 alienPos = Vec2(alienObj->box.x - alienObj->box.w / 2.0, 
                      alienObj->box.y - alienObj->box.h / 2.0);
  Vec2 target = alienPos + minionPos;

  arc += dt * PI * 2 / 10;

  this->associated.angleDeg = (Vec2(associated.box.x, associated.box.y) - alienPos).GetAngle() * 180 / PI;
  this->associated.box.x = target.x - this->associated.box.w/2.0;
  this->associated.box.y = target.y - this->associated.box.h/2.0;
}

void Minion::Shoot(Vec2 target) {
  GameObject *bullet = new GameObject();

  float angle = (target - Vec2(associated.box.x + associated.box.w / 2, associated.box.y + associated.box.h / 2)).GetAngle();

  bullet->AddComponent(new Bullet(*bullet, angle, 500, 1, 1000, "./assets/img/minionbullet1.png"));
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