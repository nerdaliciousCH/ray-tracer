#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vector {
public:
    float x;
    float y;
    float z;
    Vector(float xyz);
    Vector(float x, float y, float z);
    static float dot(Vector a, Vector b);
    Vector operator+(const Vector& other);
    Vector operator-(const Vector& other);
    Vector operator*(const float factor);
    Vector operator/(const float factor);
    void print();
};

#endif
