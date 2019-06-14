#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <math.h>
#include <limits>
#include "../math/vector.h"
#include "../color/color.h"
#include "intersectable.h"

class Plane : public Intersectable {
public:
  Vector normal;
  Vector point;
  Plane(Vector point, Vector normal, Color color, TraceType type);
  float intersect(Ray *ray);
  Vector getReflectionsDirection(Ray *ray, float t);
  Vector getNormal(Vector surface_point);
  void print();
};

#endif
