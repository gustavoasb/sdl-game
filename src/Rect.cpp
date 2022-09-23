#include "Rect.h"
using namespace std;

Rect::Rect(){
  this->x = 0;
  this->y = 0;
  this->w = 0;
  this->h = 0;
}

bool Rect::Contains(float x, float y){
  if(x >= this->x && x <= this->x + this->w && y >= this->y && y <= this->y + this->h){
    return true;
  } 
  return false;
}