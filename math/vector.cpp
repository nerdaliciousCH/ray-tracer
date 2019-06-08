#include "vector.h"

Vector::Vector(float x, float y, float z):
    x(x),
    y(y),
    z(z){
}

void Vector::print() {
    std::cout << "x: " << x << "\ty: " << y << "\tz: " << z << std::endl;
}
