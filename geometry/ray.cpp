#include "ray.h"

Ray::Ray(Vector origin, Vector direction) :
origin(origin),
direction(direction){

}

void Ray::print(){
    std::cout << "position: ";
    origin.print();
    std::cout << "direction: ";
    direction.print();
}
