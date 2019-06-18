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
  int random_samples;
  Color color;
  Sphere *light;
  std::vector<Intersectable *> *intersectables;
public:
  Path(Ray *initial_ray, std::vector<Intersectable *> *intersectables, Sphere *light, int max_path_length, int random_samples);
  void trace();
  void find_intersection(Ray* ray_in, Hit* hit);
  static void get_shadow_ray(Ray *ray_in, Hit* hit_in, Sphere* light, Ray* ray_out);
  static void get_reflection_ray(Ray *ray_in, Hit* hit_in, Ray* ray_out);
  static void get_stochastic_hemisphere_ray(Ray *ray_in, Hit* hit_in, Ray *ray_out);
  Color getColor();
};

#endif
