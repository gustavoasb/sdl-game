#ifndef _CAMERA_FOLLOWER_H
#define _CAMERA_FOLLOWER_H

#include "Component.h"

class CameraFollower : public Component{
  public:
    CameraFollower(GameObject& go);
    void Update(float dt);
    void Render();
    bool Is(string type);
    void Start();
};

#endif