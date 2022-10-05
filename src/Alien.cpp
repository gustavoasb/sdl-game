#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"
#include <iostream>
#define PI 3.14159265358979323846
#include "State.h"
#include "Game.h"
#include "Collider.h"
#include "Bullet.h"
#include "PenguinBody.h"
#define REST_TIME 0.8f

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated){
  Sprite *sprite = new Sprite(associated, "./assets/img/alien.png");
  associated.AddComponent(sprite);
  Collider *col = new Collider(associated);
  associated.AddComponent(col);
  this->speed = Vec2(0.1, 0.1);
  this->hp = 50;
  taskQueue = std::queue<Action>();
  minionArray = std::vector<std::weak_ptr<GameObject>>(nMinions);
  alienCount++;
  state = RESTING;
}

Alien::~Alien(){
  alienCount--;
  this->minionArray.clear();
}

void Alien::Update(float dt){
  associated.angleDeg += dt * 60 * -1;

  //checa se morreu
  if (!hp){
    associated.RequestDelete();

    GameObject *go = new GameObject();
    go->box.x = associated.box.x;
    go->box.y = associated.box.y;
    go->AddComponent(new Sprite(*go, "assets/img/aliendeath.png", 4, 0.1, 0.35));

    Game::GetInstance().GetState().AddObject(go);
  }

  //controla estados
  if(state == RESTING){
    if(restTimer.Get() > REST_TIME){
      state = MOVING;
      restTimer.Restart();
      destination = PenguinBody::player->GetCenter();
    }
    restTimer.Update(dt);
  }

  if(state == MOVING){
    Vec2 pos = Vec2(associated.box.x, associated.box.y);
    Vec2 pPos = PenguinBody::player->GetCenter();
    float diff = PenguinBody::player->GetCenter().distanceSquared(pos);
    cout << diff << endl;
    if(diff < 400){
      this->taskQueue.push(Action(Action::SHOOT,pPos.x, pPos.y));
      state = RESTING;
    } else{
      float angle = (pPos - associated.box.GetCenter()).GetAngle();
      Vec2 dest = pos + this->speed.GetRotated(angle);
      this->taskQueue.push(Action(Action::MOVE,destination.x,destination.y));
    }
  }

  //executa tarefas
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
        auto minion = minionArray[0].lock();
        for (unsigned int i = 1; i < minionArray.size(); i++) {
          auto minion2 = minionArray[i].lock();
          if (Vec2(minion2->box.x, minion2->box.y).distance(action.pos) < Vec2(minion->box.x, minion->box.y).distance(action.pos)){
            minion = minion2;
          }
        }
        if(minion) {
          static_cast<Minion *>(minion->GetComponent("Minion"))->Shoot(action.pos);
        }
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

void Alien::Start(){
  for (size_t i = 0; i < minionArray.size(); i++) {
    State &state = Game::GetInstance().GetState();
    auto alien = state.GetObjectPtr(&associated);
    float arcOffsetDeg = i * PI * 2 / minionArray.size();;

    GameObject *obj = new GameObject();
    Minion *minion = new Minion(*obj, alien, arcOffsetDeg);
    obj->AddComponent(minion);

    minionArray[i] = state.AddObject(obj);
  }
}

Alien::Action::Action(Action::ActionType type, float x, float y) {
  this->type = type;
  this->pos = Vec2(x, y);
}

void Alien::NotifyCollision(GameObject &other) {
  if (other.GetComponent("Bullet") != nullptr) {
    Bullet *bullet = (Bullet *)other.GetComponent("Bullet");
    if(!bullet->targetsPlayer){
      hp -= bullet->GetDamage();
    }
  }
}
