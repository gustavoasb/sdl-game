#include "Music.h"
#include <iostream>

Music::Music(){
  this->music = nullptr;
}

Music::Music(string file){
  Open(file);
}

void Music::Play(int times = -1){
  if(this->music != nullptr){
    Mix_PlayMusic(this->music, times);
  }
}

void Music::Stop(int msToStop = 1500){
  Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file){
  if(this->music != nullptr){
    Mix_LoadMUS(file.c_str());
  }
}

bool Music::IsOpen(){
  if(this->music != nullptr){
    return true;
  }
  return false;
}

Music::~Music(){
  Stop();
  Mix_FreeMusic(this->music);
}