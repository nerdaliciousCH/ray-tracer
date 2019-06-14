#ifndef HIT_H
#define HIT_H

#include "../geometry/intersectable.h"
#include "../geometry/ray.h"

struct Hit {
  Intersectable *object;
  Ray *ray;
  float t;
};

#endif
