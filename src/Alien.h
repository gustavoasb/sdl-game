#ifndef _ALIEN_H
#define _ALIEN_H

#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"
#include <queue>

class Alien : public Component{
  public:
    Alien(GameObject& associated, int nMinions);
    ~Alien();
    void Update(float dt);
    void Render();
    bool Is(string type);
    void Start();
    void NotifyCollision(GameObject &other);
  private:
  
    class Action{
      public:
        enum ActionType{MOVE, SHOOT};

        Action(ActionType type, float x, float y);

        ActionType type;
        Vec2 pos;
    };

    Vec2 speed;
    int hp;
    std::queue<Action> taskQueue;
    std::vector<std::weak_ptr<GameObject>> minionArray;
};

#endif