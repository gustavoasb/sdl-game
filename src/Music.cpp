#include "Music.h"
#include <iostream>

Music::Music(){
  this->music = nullptr;
}

Music::Music(string file){
  this->Open(file);
}

void Music::Play(int times){
  if(this->music != nullptr){
    Mix_PlayMusic(this->music, times);
  }
}

void Music::Stop(int msToStop){
  Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file){
  this->music = Mix_LoadMUS(file.c_str());
  if(this->music == nullptr){
    cout << "Falha ao iniciar musica" << endl;
    cout << SDL_GetError() << endl;
    exit(1);
  }
}

bool Music::IsOpen(){
  if(this->music != nullptr){
    return true;
  }
  return false;
}

Music::~Music(){
  this->Stop();
  Mix_FreeMusic(this->music);
}