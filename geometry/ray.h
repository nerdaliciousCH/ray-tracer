#ifndef RAY_H
#define RAY_H

#include <iostream>

#include "../math/vector.h"

class Ray {
private:
  Vector origin;
  Vector direction;
public:
  Ray(Vector origin, Vector direction);
  void print();
};

#endif
