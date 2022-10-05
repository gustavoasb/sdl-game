#ifndef _SPRITE_H
#define _SPRITE_H

#include <string>
#include <SDL2/SDL.h>
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Component.h"
#include "Vec2.h"
using namespace std;

class Sprite : public Component{
  public:
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, string file);
    ~Sprite();
    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    void Update(float dt);
    void Render(float x, float y);
    void Render();
    bool Is(string type);
    void Start();
    void SetScaleX(Vec2 scale);
    Vec2 GetScale();
  private:
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
    Vec2 scale;
};

#endif