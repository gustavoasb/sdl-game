#include "Face.h"
#include "GameObject.h"
#include <string>
using namespace std;

Face::Face(GameObject& associated) : Component(associated){
  this->hitpoints = 30;
}

void Face::Damage(int damage){
  this->hitpoints -= damage;
  if(this->hitpoints <= 0){
    this->associated.RequestDelete();
  }
}
void Face::Update(float dt){}

void Face::Render(){}

bool Face::Is(string type){
  if(type == "Face"){
    return true;
  }
  return false;
}