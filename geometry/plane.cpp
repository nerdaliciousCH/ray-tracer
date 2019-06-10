#include "plane.h"

Plane::Plane(Vector point, Vector normal, Color color, bool isLight, bool isReflective) :
    Intersectable(color, isLight, isReflective),
    point(point),
    normal(normal){
    }

float Plane::intersect(Ray ray) {
    float ln = Vector::dot(ray.direction, normal);
    float t = Vector::dot((point - ray.origin), normal) / ln;
    if (t >= 0){ // TODO maybe add some error margin. or we are stuck in plane
        return t;
    } else {
        return std::numeric_limits<float>::max();
    }

}

Vector Plane::getNormal(Vector a){
    return normal;
}

Vector Plane::getReflectionsDirection(Ray ray, float t) {
    return ray.direction - normal * 2 * Vector::dot(ray.direction, normal);
}

void Plane::print(){
    std::cout << "point: ";
    point.print();
    std::cout << "normal: ";
    normal.print();
}
