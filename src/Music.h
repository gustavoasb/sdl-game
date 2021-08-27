#ifndef _MUSIC_H
#define _MUSIC_H

#include <string>
#include <SDL2/SDL.h>
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
using namespace std;

class Music{
  public:
    Music();
    Music(string file);
    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(string file);
    bool IsOpen();
  private:
    Mix_Music* music;
};

#endif