#ifndef PATH_H
#define PATH_H

#include <math.h>
#include <vector>
#include "../color/color.h"
#include "../geometry/ray.h"
#include "../geometry/intersectable.h"
#include "../geometry/sphere.h"

class Path {
private:
  Ray initial_ray;
  int max_path_length;
  int path_length;
  Color color;
  std::vector<Intersectable *> intersectables;
  Sphere *light;
public:
  Path(Ray initial_ray, std::vector<Intersectable *> intersectables, Sphere *light, int max_path_length);
  void trace();
  void setColor(Color color);
  Color getColor();
};

#endif
