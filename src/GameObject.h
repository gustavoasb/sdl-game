#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include <string>
#include <vector>
#include <memory>
#include "Component.h"
#include "Rect.h"
using namespace std;

class GameObject{
  private:
    vector<unique_ptr<Component>> components;
    bool isDead;
  public:
    GameObject();
    ~GameObject();
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(string type);
    Rect box;
    void Start();
    bool started;
    double angleDeg;
    void NotifyCollision(GameObject& other);
};

#endif