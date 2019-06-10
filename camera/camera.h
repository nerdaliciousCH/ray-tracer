#ifndef CAMERA_H
#define CAMERA_H

#include "../math/vector.h"

class Camera {
private:
  Vector position;
  Vector up;
  Vector front;
public:
  Camera(Vector position, Vector up, Vector front);
  Vector getPosition();
  void print();
};

#endif
