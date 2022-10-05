#ifndef _PENGUIN_CANNON_H
#define _PENGUIN_CANNON_H

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Timer.h"

#include <memory>

class PenguinCannon : public Component {
public:
  PenguinCannon(GameObject &associated, std::weak_ptr<GameObject> penguinBody);
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void Shoot();
private:
  std::weak_ptr<GameObject> pbody;
  float angle;
  Timer bulletCooldown;
};

#endif
