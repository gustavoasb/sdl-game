#ifndef _GAME_H
#define _GAME_H

#include <string>
#include "State.h"
#define INCLUDE_SDL
#include "SDL_include.h"
#include <SDL2/SDL.h>
using namespace std;

#define GAME_NAME "Gustavo Barros 180064487"
#define GAME_WIDTH 1024
#define GAME_HEIGHT 600

class Game{
  public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
    float GetDeltaTime();
  private:
    Game(string title, int width, int height);
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;
    int frameStart;
    float dt;
    void CalculateDeltaTime();
};

#endif