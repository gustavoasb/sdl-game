#include "State.h"
#include "Vec2.h"
#include "Face.h"
#include "TileSet.h"
#include "TileMap.h"
#include "Sound.h"
#include "Camera.h"
#include "CameraFollower.h"
#include <iostream>
# define PI 3.14159265358979323846

State::State(){
  this->quitRequested = false;
  this->LoadAssets();
  this->music.Play();
}

State::~State(){
  this->objectArray.clear();
}

void State::LoadAssets(){
	this->music = *new Music("assets/audio/stageState.ogg");

  GameObject* object = new GameObject();

	this->bg = new Sprite(*object, "assets/img/ocean.jpg");
  object->AddComponent(this->bg);
  CameraFollower *cam = new CameraFollower(*object);
  object->AddComponent(cam);
  this->objectArray.emplace_back(object);

	GameObject* map = new GameObject();
	TileMap* tileMap = new TileMap(*map,"assets/map/tileMap.txt",new TileSet(64, 64, "assets/img/tileset.png"));
  map->AddComponent(tileMap);
  this->objectArray.emplace_back(map);
}

void State::Update(float dt){
	InputManager &input = InputManager::GetInstance();

	if(input.KeyPress(ESCAPE_KEY) || input.QuitRequested()){
    quitRequested = true;
  }

  if(input.KeyPress(SDLK_SPACE)) {
    Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) +
                  Vec2(input.GetMouseX(), input.GetMouseY());
    this->AddObject((int)objPos.x, (int)objPos.y);
  }

  Camera::Update(dt);

  for(vector<int>::size_type i = 0; i < this->objectArray.size(); i++){
    this->objectArray[i]->Update(dt);
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

void State::AddObject(int mouseX, int mouseY){
  GameObject* object = new GameObject();
  Sprite* enemy = new Sprite(*object, "assets/img/penguinface.png");
  object->AddComponent(enemy);
  object->box.x = mouseX - Camera::pos.x;
  object->box.y = mouseY - Camera::pos.y;
  object->box.w = enemy->GetWidth();
  object->box.h = enemy->GetHeight();
  Sound* sound = new Sound(*object, "assets/audio/boom.wav");
  object->AddComponent(sound);
  Face* face = new Face(*object);
  object->AddComponent(face);
  this->objectArray.emplace_back(object);
}