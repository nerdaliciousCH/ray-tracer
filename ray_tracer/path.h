#ifndef PATH_H
#define PATH_H

#include <math.h>
#include <vector>
#include <limits>
#include "../color/color.h"
#include "../geometry/ray.h"
#include "../geometry/intersectable.h"
#include "../geometry/sphere.h"
#include "../lighting/phong.h"
#include "hit.h"

class Path {
private:
  Ray *initial_ray;
  int max_path_length;
  int path_length;
  Color color;
  Sphere *light;
  std::vector<Intersectable *> *intersectables;
public:
  Path(Ray *initial_ray, std::vector<Intersectable *> *intersectables, Sphere *light, int max_path_length);
  void trace();
  void trace_ray(Ray* ray, Hit* hit);
  void get_shadow_ray(Ray *ray, Hit* hit, Ray* out);
  void get_reflection_ray(Ray *ray, Hit* hit, Ray* out);
  void get_stochastic_hemisphere_ray(Ray *ray, Hit* hit, Ray *out);
  void setColor(Color color);
  Color getColor();
};

#endif
