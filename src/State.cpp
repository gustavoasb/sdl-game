#include "State.h"
#include "Vec2.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Sound.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collision.h"
#include "Collider.h"
#include <iostream>
#define PI 3.14159265358979323846

State::State(){
  this->started = false;
  this->quitRequested = false;

  GameObject* object = new GameObject();

	this->bg = new Sprite(*object, "assets/img/ocean.jpg");
  object->AddComponent(this->bg);

	TileMap* tileMap = new TileMap(*object,"assets/map/tileMap.txt",new TileSet(64, 64, "assets/img/tileset.png"));
  object->AddComponent(tileMap);
  this->objectArray.emplace_back(object);

  CameraFollower *cam = new CameraFollower(*object);
  object->AddComponent(cam);
  this->objectArray.emplace_back(object);

  GameObject* obj = new GameObject();
  obj->box.x = 512 + Camera::pos.x;
  obj->box.y = 300 + Camera::pos.x;
  Alien* alien = new Alien(*obj, 4);
  obj->AddComponent(alien);
  objectArray.emplace_back(obj);

  GameObject* pobj = new GameObject();
  pobj->box.x = 704 + Camera::pos.x;
  pobj->box.y = 604 + Camera::pos.x;
  PenguinBody* penguin = new PenguinBody(*pobj);
  pobj->AddComponent(penguin);
  objectArray.emplace_back(pobj);
  Camera::Follow(pobj);
}

State::~State(){
  this->objectArray.clear();
}

void State::Start(){
  this->LoadAssets();
  for(vector<int>::size_type i = 0; i < objectArray.size(); i++){
    objectArray[i]->Start();
  }
  this->started = true;
}

void State::LoadAssets(){
	this->music = *new Music("assets/audio/stageState.ogg");

  this->music.Play();
}

void State::Update(float dt){
	InputManager &input = InputManager::GetInstance();

	if(input.KeyPress(ESCAPE_KEY) || input.QuitRequested()){
    quitRequested = true;
  }

  Camera::Update(dt);

  for(vector<int>::size_type i = 0; i < this->objectArray.size(); i++){
    this->objectArray[i]->Update(dt);

    Collider* col1 = (Collider*) objectArray[i]->GetComponent("Collider");
    if(col1 != nullptr){
      for(vector<int>::size_type j = i+1; j < this->objectArray.size(); j++){
        Collider* col2 = (Collider*) objectArray[j]->GetComponent("Collider");
        if(col2 != nullptr){
          if(Collision::IsColliding(col1->box, col2->box, objectArray[i]->angleDeg, objectArray[j]->angleDeg)){
            objectArray[i]->NotifyCollision(*objectArray[j]);
            objectArray[j]->NotifyCollision(*objectArray[i]);
          }
        }
      }
    }
    
    if(this->objectArray[i]->IsDead()){
      this->objectArray.erase(this->objectArray.begin() + i);
    }
  }
}

void State::Render(){
  for(vector<int>::size_type i = 0; i < this->objectArray.size(); i++){
    this->objectArray[i]->Render();
  }
}

bool State::QuitRequested(){
  return this->quitRequested;
}

weak_ptr<GameObject> State::AddObject(GameObject* go){
  shared_ptr<GameObject> object = shared_ptr<GameObject>(go);
  objectArray.push_back(object);
  if(this->started){
    object->Start();
  }
  return weak_ptr<GameObject>(object);
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){
  for(vector<int>::size_type i = 0; i < objectArray.size(); i++){
    if(objectArray[i].get() == go){
      return weak_ptr<GameObject>(objectArray[i]);
    }
  }
  return weak_ptr<GameObject>();
}