#ifndef PHONG_H
#define PHONG_H

#include <math.h>

#include "../color/color.h"
#include "../ray_tracer/hit.h"
#include "../math/vector.h"

class PhongModel {
public:
  static Color calculate(Ray* camera_ray, Hit* hit, Vector*light_position, Color* light_color);
};

#endif
