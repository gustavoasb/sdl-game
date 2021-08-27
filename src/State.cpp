#include "State.h"

State::State(){
  this->QuitRequested();
  
  // Instancia Sprite 
}

void State::LoadAssets(){
  // inicializar assets aqui sempre q possivel
}

void State::Update(float dt){
  if(SDL_QuitRequested()){
    this->quitRequested = true;
  }
}

void State::Render(){
  //chamar render do fundo
}

bool State::QuitRequested(){
  return this->quitRequested;
}