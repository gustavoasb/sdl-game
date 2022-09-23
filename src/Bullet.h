#ifndef _BULLET_H
#define _BULLET_H

#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"

class Bullet : public Component{
  public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite);
    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;
    int GetDamage();
  private:
    Vec2 speed;
    int damage;
    float distanceLeft;
};

#endif
