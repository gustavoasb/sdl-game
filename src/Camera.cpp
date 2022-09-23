#include "Camera.h"
#include "InputManager.h"
#include <iostream>

Vec2 Camera::pos = Vec2(0.0, 0.0);
Vec2 Camera::speed = Vec2(250.0, 250.0);
GameObject *Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus){
  Camera::focus = newFocus;
}

void Camera::Unfollow(){
  Camera::focus = nullptr;
}

void Camera::Update(float dt){
  if(Camera::focus == nullptr){
    InputManager &input = InputManager::GetInstance();
    if(input.IsKeyDown(UP_ARROW_KEY)) {
      Camera::pos.y -= speed.y * dt;
    }
    if(input.IsKeyDown(DOWN_ARROW_KEY)) {
      Camera::pos.y += speed.y * dt;
    }
    if(input.IsKeyDown(LEFT_ARROW_KEY)) {
      Camera::pos.x -= speed.x * dt;
    }
    if(input.IsKeyDown(RIGHT_ARROW_KEY)) {
      Camera::pos.x += speed.x * dt;
    }
  }
}