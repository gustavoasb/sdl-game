#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "Game.h"
Game* Game::instance = nullptr;
#include "SDL_include.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game& Game::GetInstance(){
  if(Game::instance != nullptr){
    return *Game::instance;
  }
  new Game(GAME_NAME, GAME_WIDTH, GAME_HEIGHT);
  return *Game::instance;
}

Game::Game(string title, int width, int height){
  if(Game::instance != nullptr){
    cout << "Instance nao eh nullptr" << endl;
    return;
  }

  Game::instance = this;

  // Inicia SDL
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
    cout << "Falha ao iniciar SDL" << endl;
    cout << SDL_GetError() << endl;
    exit(1);
  }
  
  // Inicia Imagens
  if(!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)){
    cout << "Falha ao iniciar imagens" << endl;
    cout << SDL_GetError() << endl;
    exit(1);
  }

  // Inicia Audio
  if(!Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG)){
    cout << "Falha ao iniciar mixer" << endl;
    cout << SDL_GetError() << endl;
    exit(1);
  }
  if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)){
    cout << "Falha ao iniciar audio" << endl;
    cout << SDL_GetError() << endl;
    exit(1);
  }
  if(!(Mix_AllocateChannels(32))){
    cout << "Falha ao alocar canais necessarios" << endl;
    cout << SDL_GetError() << endl;
    exit(1);
  }

  // Cria janela
  this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  if(this->window == nullptr){
    cout << "Falha ao iniciar janela" << endl;
    cout << SDL_GetError() << endl;
    exit(1);
  }

  // Cria Renderer
  this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
  if(this->renderer == nullptr){
    cout << "Falha ao iniciar renderer" << endl;
    cout << SDL_GetError() << endl;
    exit(1);
  }

  this->state = new State();

  //Seed
  srand(time(NULL));

  // Inicializa dt e frameStart
  this->dt = 0;
  this->frameStart = 0;
}

Game::~Game(){
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
}

State& Game::GetState(){
  return *this->state;
}

SDL_Renderer* Game::GetRenderer(){
  return this->renderer;
}

void Game::Run(){
  this->state->Start();
  while(!(this->state->QuitRequested())){
    this->CalculateDeltaTime();
    InputManager::GetInstance().Update();
    this->state->Update(this->GetDeltaTime());
    this->state->Render();
    SDL_RenderPresent(this->renderer);
    SDL_Delay(33);
  }
}

void Game::CalculateDeltaTime(){
   int frameTime = SDL_GetTicks();

  this->dt = (frameTime - this->frameStart) / (float)1000;
  this->frameStart = frameTime;
}

float Game::GetDeltaTime(){
  return this->dt;
}