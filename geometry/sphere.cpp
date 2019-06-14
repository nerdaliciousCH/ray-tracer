#include "sphere.h"

Sphere::Sphere(float radius, Vector center, Color color, TraceType type) :
    Intersectable(color, type),
    radius(radius),
    center(center){}

float Sphere::intersect(Ray *ray) {
    // t^2 * (dir dot dir) +
    // 2 * t * (dir dot (origin - center)) +
    // ((origin - center) dot (origin - center) - r^2) = 0
    // Is of form a*t^2 + b*t + c = 0
    float ray_direction_squared = Vector::dot(ray->direction, ray->direction); // dir dot dir
    Vector diff_ray_origin_center = ray->origin - center; // (origin - center)
    float radius_squared = radius * radius; // r^2

    float a = ray_direction_squared;
    float b = 2 * Vector::dot(ray->direction, diff_ray_origin_center);
    float c = Vector::dot(diff_ray_origin_center, diff_ray_origin_center) - radius_squared;

    float discriminant = b*b-4*a*c;

    if (discriminant > 0) {
        // Hit sphere
        float squareroot_discriminant = sqrt(discriminant);
        float t1 = (-b+squareroot_discriminant)/(2 * a);
        float t2 = (-b-squareroot_discriminant)/(2 * a);

        if (t1 <= 0 && t2 <= 0) {
            // Intersection is behind us or we are inside it...
            return std::numeric_limits<float>::max();
        }
        if(t1 <= 0) {
            return t2;
        }
        if(t2 <= 0) {
            return t1;
        }
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

Vector Sphere::getNormal(Vector surface_point){
    return Vector::normalize(surface_point - center);
}

Vector Sphere::getReflectionsDirection(Ray *ray, float t) {
    Vector point = ray->origin + ray->direction * t;
    Vector normal = Vector::normalize(point - center);
    return ray->direction - normal * 2 * Vector::dot(ray->direction, normal);
}

void Sphere::print(){
    std::cout << "r: " << radius << std::endl;
    color.print();
    center.print();
}
