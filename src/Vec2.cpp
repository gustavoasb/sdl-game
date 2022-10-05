#include "Vec2.h"
#include <math.h>
using namespace std;

Vec2::Vec2(){
  this->x = 0;
  this->y = 0;
}

Vec2::Vec2(float x, float y){
  this->x = x;
  this->y = y;
}

Vec2 Vec2::GetRotated(float angle){
  float x = this->x * cos(angle) - this->y * sin(angle);
  float y = this->y * cos(angle) + this->x * sin(angle);
  return Vec2(x, y);
}

Vec2 operator + (Vec2 const &c1, Vec2 const &c2)
{
  return Vec2(c1.x + c2.x, c1.y + c2.y);
}

Vec2 operator - (Vec2 const &c1, Vec2 const &c2)
{
  return Vec2(c1.x - c2.x, c1.y - c2.y);
}

Vec2 operator * (Vec2 const &c1, float const &n)
{
  return Vec2(c1.x * n, c1.y * n);
}

float Vec2::length() { 
  return sqrt(this->x * this->x + this->y * this->y); 
}

float Vec2::GetAngle(){ 
  return atan2(this->y, this->x); 
}

float Vec2::distance(Vec2 v) {
  return (this->x - v.x) * (this->x - v.x) + (this->y - v.y) * (this->y - v.y);
}

float Vec2::distanceSquared(Vec2 v) {
  return sqrt((this->x - v.x) * (this->x - v.x) + (this->y - v.y) * (this->y - v.y));
}
