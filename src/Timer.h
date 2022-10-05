#ifndef _TIMER_H
#define _TIMER_H

class Timer {
  public:
    Timer();
    void Update(float dt);
    void Restart();
    float Get();
  private:
    float time;
};

#endif