#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include <iostream>

Alien::Alien(GameObject& associated, int nMinions) : Component(associated){
  Sprite *sprite = new Sprite(associated, "./assets/img/alien.png");
  associated.AddComponent(sprite);
  this->speed = Vec2(1.5, 1.5);
  this->hp = 50;
  taskQueue = std::queue<Action>();
  minionArray = std::vector<std::weak_ptr<GameObject>>(nMinions);
}

Alien::~Alien(){
  this->minionArray.clear();
}

void Alien::Update(float dt){
  InputManager& input = InputManager::GetInstance();

  if(input.MousePress(SDL_BUTTON_LEFT)){
    this->taskQueue.push(Action(Action::SHOOT,input.GetMouseX() - Camera::pos.x,input.GetMouseY() - Camera::pos.y));
  }
  if(input.MousePress(SDL_BUTTON_RIGHT)){
    this->taskQueue.push(Action(Action::MOVE,input.GetMouseX() - Camera::pos.x,input.GetMouseY() - Camera::pos.y));
  }

  if(!taskQueue.empty()){
    Action action = this->taskQueue.front();
    switch(action.type){
      case Action::MOVE: {
        Vec2 dif = (action.pos - Vec2(associated.box.x, associated.box.y)) * (float)0.1;
        if(dif.length() < 0.15){
          taskQueue.pop();
        } else{
          associated.box.x += dif.x*pow(0.8, dt*this->speed.x);
          associated.box.y += dif.y*pow(0.8, dt*this->speed.y);
        }
        break;
      }
      case Action::SHOOT: {
        taskQueue.pop();
        break;
      }
      default:
        taskQueue.pop();
        break;
    }
  }
}

void Alien::Render(){}

bool Alien::Is(string type){
  if(type == "Alien"){
    return true;
  }
  return false;
}

void Alien::Start(){}

Alien::Action::Action(Action::ActionType type, float x, float y) {
  this->type = type;
  this->pos = Vec2(x, y);
}