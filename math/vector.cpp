#include "vector.h"

Vector::Vector(float xyz):
    x(xyz),
    y(xyz),
    z(xyz){

    }

Vector::Vector(float x, float y, float z):
    x(x),
    y(y),
    z(z){
}

float Vector::dot(Vector a, Vector b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector Vector::cross(Vector a, Vector b) {
    float cross_x = a.y*b.z - a.z*b.y;
    float cross_y = a.z*b.x - a.x*b.z;
    float cross_z = a.x*b.y - a.y*b.x;
    return Vector(cross_x, cross_y, cross_z);
}

Vector Vector::normalize(Vector a) {
    float length = a.length();
    return Vector(a.x/length, a.y/length, a.z/length);
}

float Vector::length() {
    return sqrt(x*x + y*y + z*z);
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

bool Vector::operator==(const Vector& other) {
    return std::abs(x - other.x) < EPSILON && std::abs(y - other.y) < EPSILON && std::abs(z - other.z) < EPSILON;
}

bool Vector::operator!=(const Vector& other) {
    return std::abs(x - other.x) >= EPSILON || std::abs(y - other.y) >= EPSILON || std::abs(z - other.z) >= EPSILON;
}

void Vector::print() {
    std::cout << "x: " << x << "\ty: " << y << "\tz: " << z << std::endl;
}
