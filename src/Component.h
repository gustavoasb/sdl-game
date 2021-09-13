#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <string>
class GameObject;
using namespace std;

class Component{
  protected:
    GameObject& associated;
  public:
    Component(GameObject& associated);
    virtual ~Component();
    void virtual Update(float dt) = 0;
    void virtual Render() = 0;
    bool virtual Is(string type) = 0;
};

#endif