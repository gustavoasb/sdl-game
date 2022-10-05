#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <string>
#include <iostream>
class GameObject;
using namespace std;

class Component{
  protected:
    GameObject& associated;
  public:
    Component(GameObject& associated);
    virtual ~Component();
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual bool Is(string type) = 0;
    virtual void Start(){};
    virtual void NotifyCollision(GameObject& other){};
};

#endif