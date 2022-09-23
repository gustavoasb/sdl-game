#include "Bullet.h"
#include "Sprite.h"
#define PI 3.14159265358979323846

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage,
  float maxDistance, std::string sprite) : Component(associated){
  this->damage = damage;
  this->distanceLeft = maxDistance;
  this->speed = Vec2(speed, (float)0).GetRotated(angle);
  associated.angleDeg = angle * 180 / PI;

  Sprite *sprite2 = new Sprite(associated, sprite);
  associated.AddComponent(sprite2);
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
