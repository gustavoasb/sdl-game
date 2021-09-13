#ifndef _FACE_H
#define _FACE_H

#include <string>
#include "GameObject.h"
using namespace std;

class Face : public Component{
  private:
    int hitpoints;
  public:
    Face(GameObject& associated);
    void Damage(int damage);
    void Update(float dt);
    void Render();
    bool Is(string type);
};

#endif