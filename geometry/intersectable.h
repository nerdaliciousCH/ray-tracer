#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H

#include "../math/vector.h"
#include "../color/color.h"
#include "ray.h"

class Intersectable {
public:
  Intersectable(Color color): color(color) {};
  Color color;
  virtual float intersect(Ray ray) = 0;
  virtual Vector getReflectionsDirection(Ray ray, float t) = 0;
};

#endif
