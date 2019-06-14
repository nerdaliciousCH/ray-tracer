#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H

#include "../math/vector.h"
#include "../color/color.h"
#include "ray.h"

enum class TraceType {
    normal,
    light,
    reflective,
    refractive
};

class Intersectable {
public:
    Intersectable(Color color, TraceType type):
        color(color),
        type(type)
        {};
  TraceType type;
  Color color;
  virtual float intersect(Ray ray) = 0;
  virtual Vector getReflectionsDirection(Ray ray, float t) = 0;
  virtual Vector getNormal(Vector surface_point) = 0;
};

#endif
