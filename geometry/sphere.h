#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <limits>
#include <math.h>
#include "../math/vector.h"
#include "../color/color.h"
#include "intersectable.h"

class Sphere : public Intersectable {
public:
    float radius;
    Vector center;
    Sphere(float radius, Vector center, Color color, TraceType type);
    float intersect(Ray *ray);
    Vector getReflectionsDirection(Ray *ray, float t);
    Vector getNormal(Vector surface_point);
    void print();
};

#endif
