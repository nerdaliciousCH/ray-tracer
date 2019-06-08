#include "sphere.h"

Sphere::Sphere(float radius, Vector center, Color color) :
    radius(radius),
    center(center),
    color(color){
}

void Sphere::print(){
    std::cout << "r: " << radius << std::endl;
    color.print();
    center.print();
}
