#include "GameObject.h"
#include "Component.h"
#include <memory>
using namespace std;

GameObject::GameObject(){
  this->isDead = false;
}

// Corrigir
GameObject::~GameObject(){
  this->components.clear();
}

void GameObject::Update(float dt){
  for(vector<int>::size_type i = 0; i < this->components.size(); i++) {
    this->components[i]->Update(dt);
  }
}

void GameObject::Render(){
  for(vector<int>::size_type i = 0; i < this->components.size(); i++) {
    this->components[i]->Render();
  }
}

bool GameObject::IsDead(){
  return this->isDead;
}

void GameObject::RequestDelete(){
  this->isDead = true;
}

void GameObject::AddComponent(Component* cpt){
  this->components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt){
  for(vector<int>::size_type i = 0; i < this->components.size(); i++) {
    if(this->components[i].get() == cpt){
      this->components.erase(this->components.begin() + i);
    }
  }
}

Component* GameObject::GetComponent(string type){
  for(vector<int>::size_type i = 0; i < this->components.size(); i++) {
    if(this->components[i]->Is(type)){
      return this->components[i].get();
    }
  }
  return nullptr;
}
