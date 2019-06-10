#include "sphere.h"

Sphere::Sphere(float radius, Vector center, Color color) :
    Intersectable(color),
    radius(radius),
    center(center){

}

float Sphere::intersect(Ray ray) {
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

        // if (t1 < 0) {
        //     t1 = std::numeric_limits<float>::max();
        // }
        // if(t2 < 0) {
        //     t2 = std::numeric_limits<float>::max();
        // }

        if(t1 < t2) {
            return t1;
        } else {
            return t2; // TODO smallest positive? Shoudl we check for
        }
    }else {
        // Missing sphere
        return std::numeric_limits<float>::max();
    }
}

Vector Sphere::getReflectionsDirection(Ray ray, float t) {
    Vector point = ray.origin + ray.direction * t;
    Vector normal = Vector::normalize(point - center);
    return ray.direction - normal * 2 * Vector::dot(ray.direction, normal); 
}

void Sphere::print(){
    std::cout << "r: " << radius << std::endl;
    color.print();
    center.print();
}
