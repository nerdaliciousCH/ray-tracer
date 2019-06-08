#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include "../math/vector.h"
#include "../color/color.h"

class Sphere {
private:
  float radius;
  Vector center;
  Color color;

public:
  Sphere(float radius, Vector center, Color color);
  void print();
  // ostream& operator<<(ostream& os, const Sphere& sphere);
};

#endif
