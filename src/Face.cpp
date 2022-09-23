#include "Face.h"
#include "Sound.h"
#include "GameObject.h"
#include <string>
#include <chrono>
#include <thread>
#include "Camera.h"
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
void Face::Update(float dt){
  InputManager &input = InputManager::GetInstance();
  if(input.MousePress(SDL_BUTTON_LEFT)){
		if(associated.box.Contains((float)(input.GetMouseX() + Camera::pos.x), (float)(input.GetMouseY() + Camera::pos.y))){
			this->Damage(std::rand() % 10 + 10);
		}
	}
}

void Face::Render(){}

bool Face::Is(string type){
  if(type == "Face"){
    return true;
  }
  return false;
}