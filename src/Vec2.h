#ifndef _VEC2_H
#define _VEC2_H

class Vec2{
  public:
    Vec2();
    Vec2(float x, float y);
    float x;
    float y;
    Vec2 GetRotated(float angle);
    friend Vec2 operator + (Vec2 const &, Vec2 const &);
    friend Vec2 operator - (Vec2 const &, Vec2 const &);
    friend Vec2 operator * (Vec2 const &, float const &);
    float length();
    float GetAngle();
    float distance(Vec2 v);

};

#endif