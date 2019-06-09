#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include "../math/vector.h"
#include "../color/color.h"
#include "intersectable.h"

class Cube : public Intersectable {
public:
  Vector center;
  float height;
  float width;
  float depth;
  Cube(Vector center, float height, float width, float depth, Color color);
  Vector intersect(Ray ray);
  void print();
};

#endif
