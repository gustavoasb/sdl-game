#include "InputManager.h"

InputManager& InputManager::GetInstance(){
  static InputManager input;
  return input;
}

InputManager::InputManager(){
  this->quitRequested = false;
  this->updateCounter = 0;
  this->mouseX = 0;
  this->mouseY = 0;
  for(int i = 0; i < 6; i++){
    mouseState.push_back(false);
    mouseUpdate.push_back(false);
  }
}

InputManager::~InputManager(){}

void InputManager::Update(){
  SDL_Event ev;

  SDL_GetMouseState(&this->mouseX, &this->mouseY);

  this->updateCounter++;

  while(SDL_PollEvent(&ev)){
    if(ev.key.repeat) continue;
    switch(ev.type){
      case SDL_KEYDOWN:
        keyState[ev.key.keysym.sym] = true;
        keyUpdate[ev.key.keysym.sym] = this->updateCounter;
        break;
      case SDL_KEYUP:
        keyState[ev.key.keysym.sym] = false;
        keyUpdate[ev.key.keysym.sym] = this->updateCounter;
        break;
      case SDL_MOUSEBUTTONDOWN:
        this->mouseState[ev.button.button] = true;
        this->mouseUpdate[ev.button.button] = this->updateCounter;
        break;
      case SDL_MOUSEBUTTONUP:
        this->mouseState[ev.button.button] = false;
        this->mouseUpdate[ev.button.button] = this->updateCounter;
        break;
      case SDL_QUIT:
        this->quitRequested = true;
        break;
      default:
        break;
    }
  };
}

bool InputManager::KeyPress(int key){
  if(this->keyUpdate[key] == updateCounter){
    return this->keyState[key];
  }
  return false;
}

bool InputManager::KeyRelease(int key){
  if(this->keyUpdate[key] == updateCounter){
    return !this->keyState[key];
  }
  return false;
}

bool InputManager::MousePress(int button){
  if(this->mouseUpdate[button] == updateCounter){
    return this->mouseState[button];
  }
  return false;
}

bool InputManager::MouseRelease(int button){
  if(this->mouseUpdate[button] == updateCounter){
    return !this->mouseState[button];
  }
  return false;
}

bool InputManager::IsKeyDown(int key){
  return this->keyState[key];
}

bool InputManager::IsMouseDown(int button){
  return this->mouseState[button];
}

int InputManager::GetMouseX(){
  return this->mouseX;
}

int InputManager::GetMouseY(){
  return this->mouseY;
}

bool InputManager::QuitRequested(){
  return this->quitRequested;
}