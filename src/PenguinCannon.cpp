#include "PenguinCannon.h"
#include "PenguinBody.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Game.h"
#include "Camera.h"
#include <iostream>
#include "Collider.h"
#define PI 3.14159265358979323846

PenguinCannon::PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody) : Component(associated) {
  Sprite *sprite = new Sprite(associated, "assets/img/cubngun.png");
  associated.AddComponent(sprite);

  Collider *col = new Collider(associated);
  associated.AddComponent(col);
}

void PenguinCannon::Update(float dt){
  if(PenguinBody::player == nullptr) {
    associated.RequestDelete();
    return;
  }

  Vec2 bodyPos = PenguinBody::player->GetCenter();
  associated.box.x = bodyPos.x - associated.box.w / 2;
  associated.box.y = bodyPos.y - associated.box.h / 2;

  InputManager &input = InputManager::GetInstance();

  Vec2 mouse = Vec2(input.GetMouseX(), input.GetMouseY()) + Camera::pos;
  angle = (mouse - associated.box.GetCenter()).GetAngle();
  associated.angleDeg = angle * 180 / PI;
  
  if(input.MousePress(SDL_BUTTON_LEFT)){
    this->Shoot();
  }
}

void PenguinCannon::Render(){}

bool PenguinCannon::Is(std::string type){
  if(type == "PenguinCannon"){
    return true;
  }
  return false;
}

void PenguinCannon::Shoot(){
  GameObject *bullet = new GameObject();

  bullet->AddComponent(new Bullet(*bullet, this->angle, 500, 5, 1000, "./assets/img/penguinbullet.png", false));
  bullet->box.x = this->associated.box.x - bullet->box.w / 2.0;
  bullet->box.y = this->associated.box.y - bullet->box.h / 2.0;

  Game::GetInstance().GetState().AddObject(bullet);
}