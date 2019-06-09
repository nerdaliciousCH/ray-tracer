#include "sphere.h"

Sphere::Sphere(float radius, Vector center, Color color) :
    Intersectable(color),
    radius(radius),
    center(center){

}

Vector Sphere::intersect(Ray ray) {
    float r2 = radius * radius;
    Vector v = center - ray.origin;
    float d2 = Vector::dot(ray.direction, ray.direction);
    float twice_vd = Vector::dot(v, ray.direction) * 2;
    float v_minus_r = Vector::dot(v, v) - r2;
    float discriminant = twice_vd * twice_vd - 4 * d2 * v_minus_r;
    if (discriminant > 0) {
        // Hit spere
        float sqr_disc = sqrt(discriminant);
        float t1 = (-twice_vd+sqr_disc)/(2 * d2);
        float t2 = (-twice_vd-sqr_disc)/(2 * d2);
        float t = 0.0f;

        if(t1 < t2) {
            t = t1;
        } else {
            t = t2; // TODO smallest positive? Shoudl we check for
        }

        return ray.origin + ray.direction * t;
    }else {
        // Missing sphere
        return Vector(0.0);
    }
}

void Sphere::print(){
    std::cout << "r: " << radius << std::endl;
    color.print();
    center.print();
}
