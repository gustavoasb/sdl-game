#ifndef _STATE_H
#define _STATE_H

#include "InputManager.h"

#include <string>
#include <SDL2/SDL.h>
#include "Sprite.h"
#include "Music.h"
#include <vector>
#include <memory>
using namespace std;

class State{
  public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
  private:
    Sprite* bg;
    Music music;
    bool quitRequested;
    void AddObject(int mouseX, int mouseY);
    vector<unique_ptr<GameObject>> objectArray;
};

#endif