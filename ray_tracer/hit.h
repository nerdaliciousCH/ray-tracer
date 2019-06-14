#ifndef HIT_H
#define HIT_H

#include <limits>

#include "../geometry/intersectable.h"
#include "../geometry/ray.h"

struct Hit {
  Intersectable *object;
  Ray *ray;
  float t;
  Hit(): object(NULL), ray(NULL), t(std::numeric_limits<float>::max()) {};
};

#endif
