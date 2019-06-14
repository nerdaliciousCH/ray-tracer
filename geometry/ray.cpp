#include "ray.h"

Ray::Ray() : origin(Vector(0)), direction(Vector(0, 0, -1)){}

Ray::Ray(Vector origin, Vector direction) :
origin(origin),
direction(direction){
    this->direction = Vector::normalize(direction);
}

void Ray::print(){
    std::cout << "position: ";
    origin.print();
    std::cout << "direction: ";
    direction.print();
}
