#include "State.h"
#include <iostream>

State::State(){
  this->quitRequested = false;
  this->bg = *new Sprite("assets/img/ocean.jpg");
  this->music = *new Music("assets/audio/stageState.ogg");
  music.Play();
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
  this->bg.Render(0, 0);
}

bool State::QuitRequested(){
  return this->quitRequested;
}