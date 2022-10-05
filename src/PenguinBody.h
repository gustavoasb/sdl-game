#ifndef _PENGUIN_BODY_H
#define _PENGUIN_BODY_H

#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"

class PenguinBody : public Component {
public:
  PenguinBody(GameObject &associated);
  ~PenguinBody();

  void Start();
  void Update(float dt);
  void Render();
  bool Is(std::string type);
  Vec2 GetCenter();

  static PenguinBody* player;

  void NotifyCollision(GameObject &other);
private:
  std::weak_ptr<GameObject> pcannon;
  Vec2 speed;
  float linearSpeed;
  float angle;
  int hp;
};

#endif
