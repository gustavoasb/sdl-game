#ifndef _MINION_H
#define _MINION_H

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

#include <memory>

class Minion : public Component {
public:
  Minion(GameObject &associated, std::weak_ptr<GameObject>, float arcOffsetDeg);
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void Shoot(Vec2 target);
private:
  std::weak_ptr<GameObject> alienCenter;
  float arc;
};

#endif
