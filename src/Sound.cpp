#include "Sound.h"
#include "GameObject.h"
#include <string>
#include <iostream>

using namespace std;

Sound::Sound(GameObject& associated) : Component(associated){
  this->chunk = nullptr;
}

Sound::Sound(GameObject& associated, string file) : Component(associated){
  Open(file);
}

void Sound::Play(int times){
  this->channel = Mix_PlayChannel(-1, this->chunk, times);
}

void Sound::Stop(){
  Mix_HaltChannel(this->channel); 
}

void Sound::Open(string file){
  Mix_Chunk* aux_chunk = Mix_LoadWAV(file.c_str());
  if(aux_chunk == nullptr){
    cout << "Falha ao iniciar som" << endl;
    cout << SDL_GetError() << endl;
    exit(1);
  }
  this->chunk = aux_chunk;
}

Sound::~Sound(){
  this->Stop();
  Mix_FreeChunk(this->chunk);
}

void Sound::Update(float dt){}

void Sound::Render(){}

bool Sound::Is(string type){
  if(type == "Sound"){
    return true;
  }
  return false;
}