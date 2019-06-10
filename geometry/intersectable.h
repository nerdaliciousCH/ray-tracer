#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H

#include "../math/vector.h"
#include "../color/color.h"
#include "ray.h"

class Intersectable {
public:
    Intersectable(Color color, bool isLightSource, bool isReflective):
        color(color),
        isLightSource(isLightSource),
        isReflective(isReflective)
        {};
  bool isReflective;
  bool isLightSource;
  Color color;
  virtual float intersect(Ray ray) = 0;
  virtual Vector getReflectionsDirection(Ray ray, float t) = 0;
  virtual Vector getNormal(Vector surface_point) = 0;
};

#endif
