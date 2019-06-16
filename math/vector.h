#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <math.h>

class Vector {
public:
    float EPSILON = 1.0e-4; // TODO make this a global constant
    float x;
    float y;
    float z;
    Vector(float xyz);
    Vector(float x, float y, float z);
    static float dot(Vector a, Vector b);
    static Vector cross(Vector a, Vector b);
    static Vector normalize(Vector a);
    float length();
    Vector operator+(const Vector& other);
    Vector operator-(const Vector& other);
    Vector operator*(const float factor);
    Vector operator/(const float factor);
    bool operator==(const Vector& other);
    bool operator!=(const Vector& other);
    void print();
};

#endif
