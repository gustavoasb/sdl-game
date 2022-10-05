#ifndef _RECT_H
#define _RECT_H

#include "Vec2.h"

class Rect{
  public:
    Rect(float x, float y, float w, float h);
    float x, y, w, h;
    bool Contains(float x, float y);
    Vec2 GetCenter();
};

#endif