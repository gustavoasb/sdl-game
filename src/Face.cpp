#include "Face.h"
#include "Sound.h"
#include "GameObject.h"
#include <string>
#include <chrono>
#include <thread>
using namespace std;

Face::Face(GameObject& associated) : Component(associated){
  this->hitpoints = 30;
}

void Face::Damage(int damage){
  this->hitpoints -= damage;
  Sound* sound = (Sound*) this->associated.GetComponent("Sound");
  
  if(this->hitpoints <= 0 && !this->associated.IsDead()){
    this->associated.RequestDelete();
    if(sound != nullptr){
      sound->Play();
      std::this_thread::sleep_for(1.7s);
    }
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