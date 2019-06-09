#ifndef RAY_H
#define RAY_H

#include <iostream>

#include "../math/vector.h"

class Ray {
public:
  Vector origin;
  Vector direction;
  Ray(Vector origin, Vector direction);
  void print();
};

#endif
