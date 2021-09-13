#include "Vec2.h"
#include <math.h>
using namespace std;

Vec2::Vec2(){
  this->x = 0;
  this->y = 0;
}

Vec2::Vec2(int x, int y){
  this->x = x;
  this->y = y;
}

Vec2 Vec2::GetRotated(float angle){
  x = this->x * cos(angle) - this->y * sin(angle);
  y = this->y * cos(angle) - this->x * sin(angle);
  return Vec2(x, y);
}

Vec2 operator + (Vec2 const &c1, Vec2 const &c2)
{
     return Vec2(c1.x + c2.x, c1.y + c2.y);
}