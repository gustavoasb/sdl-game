#include "Bullet.h"
#include "Sprite.h"
#include <iostream>
#include "Collider.h"
#define PI 3.14159265358979323846

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage,
  float maxDistance, std::string sprite, bool targetsPlayer) : Component(associated) {
    
  this->targetsPlayer = targetsPlayer;
  this->damage = damage;
  this->distanceLeft = maxDistance;
  this->speed = Vec2(speed, (float)0).GetRotated(angle);
  associated.angleDeg = angle * 180 / PI;

  Sprite *sprite2 = new Sprite(associated, sprite, 3, 0.1);
  associated.AddComponent(sprite2);

  Collider *col = new Collider(associated);
  associated.AddComponent(col);
}

void Bullet::Update(float dt) {
  associated.box.x += speed.x * dt;
  associated.box.y += speed.y * dt;
  distanceLeft -= speed.length() * dt;
  if (distanceLeft < 0) {
    associated.RequestDelete();
  }
}

void Bullet::Render() {}

bool Bullet::Is(std::string type){
  if(type == "Bullet"){
    return true;
  }
  return false; 
}

int Bullet::GetDamage(){ 
  return damage; 
}