#ifndef _Collider_H
#define _Collider_H

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Rect.h"

#include <memory>

class Collider : public Component {
public:
  Collider(GameObject &associated, Vec2 scale = Vec2(1, 1), Vec2 offset = Vec2(0,0));

  void Update(float dt);
  void Render();
  bool Is(std::string type);

  void SetScale(Vec2 scale);
  void SetOffset(Vec2 offset);

  Rect box;
private:
  Vec2 scale;
  Vec2 offset;
};

#endif
