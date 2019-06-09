#include "cube.h"

Cube::Cube(Vector center, float height, float width, float depth, Color color) :
    Intersectable(color),
    center(center),
    height(height),
    width(width),
    depth(depth){

}

Vector Cube::intersect(Ray ray) {
    return Vector(0.0);
}

void Cube::print(){
    std::cout << "ima cube" << std::endl;
}
