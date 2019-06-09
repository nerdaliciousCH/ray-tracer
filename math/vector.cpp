#include "vector.h"

Vector::Vector(float x, float y, float z):
    x(x),
    y(y),
    z(z){
}

float Vector::dot(Vector a, Vector b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector Vector::operator+(const Vector& other){
    Vector new_vec(
        x + other.x,
        y + other.y,
        z + other.z
    );
    return new_vec;
}

Vector Vector::operator-(const Vector& other){
    Vector new_vec(
        x - other.x,
        y - other.y,
        z - other.z
    );
    return new_vec;
}

Vector Vector::operator*(const float factor){
    Vector new_vec(
        x*factor,
        y*factor,
        z*factor
    );
    return new_vec;
}

Vector Vector::operator/(const float factor){
    Vector new_vec(
        x / factor,
        y / factor,
        z / factor
    );
    return new_vec;
}

void Vector::print() {
    std::cout << "x: " << x << "\ty: " << y << "\tz: " << z << std::endl;
}
