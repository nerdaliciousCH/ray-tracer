#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include <assert.h>

#include "../helpers/utility_functions.h"
#include "../helpers/draw_bmp.h"
#include "../geometry/intersectable.h"
#include "../geometry/plane.h"
#include "../geometry/sphere.h"
#include "../geometry/ray.h"
#include "../color/color.h"
#include "../camera/camera.h"
#include "../math/vector.h"
#include "../ray_tracer/path.h"

float EPSILON = 0.0001;

void print_success(){
    std::cout << "\xE2\x9C\x94" << std::endl;
}

void print_test_preamble(std::string name){
    std::cout << "Test " << name << ": ";
}

void test_vector() {
    print_test_preamble("Vector");
    Vector a(1.0, 0.0, 0.0);
    Vector b(0.0, 1.0, 0.0);
    Vector c(1.0, 1.0, 0.0);
    Vector normalized = Vector::normalize(c);

    assert(Vector::dot(a, b) == 0.0);
    assert(Vector::dot(a, a) == 1.0);
    assert(a != b);
    assert(a == a);
    assert(a + b == c);
    assert((a / 2).x == 0.5);
    assert((a * 2).x == 2.0);
    assert(a.length() == 1.0);
    assert((c.length() - 1.4142) < EPSILON);
    assert(normalized.length() - 1.0 < EPSILON);
    print_success();
}

void test_ray() {
    print_test_preamble("Ray");

    Vector non_normalized(1.0, 1.0, 1.0);
    Ray ray(
        Vector(0.0),
        non_normalized
    );
    assert(non_normalized.length() -1.0 > EPSILON);
    assert(ray.direction.length() - 1.0 < EPSILON);

    print_success();
}

void test_plane() {
    print_test_preamble("Plane");

    Plane plane(
        Vector(0.0, 0.0, -10.0),
        Vector(0.0, 0.0, 1.0),
        Color(255, 255, 255)
    );
    Ray ray_straight(
        Vector(0.0),
        Vector(0.0, 0.0, -1.0)
    );
    float t_straight = plane.intersect(ray_straight);
    Ray ray_non_straight(
        Vector(0.0),
        Vector(-1.0, 0.0, -1.0)
    );

    // TODO continue here. please normalize direction of ray_non_straight


    assert((ray_straight.origin + ray_straight.direction * t_straight) == plane.point);

    print_success();
}

int main(int argc, char *argv[]){
    std::cout << "Running test ..." << std::endl;
    test_vector();
    test_ray();
    test_plane();
}
