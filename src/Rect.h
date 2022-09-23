#ifndef _RECT_H
#define _RECT_H

#include <initializer_list>

class Rect{
  public:
    Rect();
    float x, y, w, h;
    bool Contains(float x, float y);
};

#endif