#include <iostream>
#include <string>
#include <assert.h>
#include <math.h>

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

// float EPSILON = 1.0e-4; TODO

void print_success(){
    std::cout << "\xE2\x9C\x94" << std::endl;
}

void print_test_preamble(std::string name){
    std::cout << "Test " << name << ": ";
}

void test_color() {
    print_test_preamble("Color");
    Color red(255, 0, 0);
    Color green(0, 255, 0);
    Color blue(0, 0, 255);
    Color magenta = red + blue;
    assert(magenta.r == 255);
    assert(magenta.g == 0);
    assert(magenta.b == 255);
    Color dark_blue = blue / 2;
    assert(dark_blue.b == 127);
    Color* address_before = &red;
    red /= 2;
    Color* address_after = &red;
    assert(red.r == 127);
    assert(red.g == 0);
    assert(red.b == 0);
    assert(address_before == address_after);
    print_success();
}

void test_vector() {
    print_test_preamble("Vector");
    Vector a(1.0, 0.0, 0.0);
    Vector b(0.0, 1.0, 0.0);
    Vector c(1.0, 1.0, 0.0);
    Vector normalized = Vector::normalize(c);
    Vector a_dot_b = Vector::dot(a, b);
    Vector a_dot_a = Vector::dot(a, a);
    Vector a_cross_b = Vector::cross(a, b);
    Vector a_cross_a = Vector::cross(a, a);

    assert(Vector::dot(a, b) == 0.0);
    assert(Vector::dot(a, a) == 1.0);
    assert(a != b);
    assert(a == a);
    assert(a + b == c);
    assert((a / 2).x == 0.5);
    assert((a * 2).x == 2.0);
    assert(a.length() == 1.0);
    assert((c.length() - 1.4142) < 1.0e-4);
    assert(normalized.length() - 1.0 < 1.0e-4);
    assert(a_dot_a == 1.0);
    assert(a_dot_b == 0.0);
    assert(a_cross_b == Vector(0.0, 0.0, 1.0));
    assert(a_cross_a == Vector(0));
    print_success();
}

void test_ray() {
    print_test_preamble("Ray");

    Vector non_normalized(1.0, 1.0, 1.0);
    Ray ray(
        Vector(0.0),
        non_normalized
    );
    assert(std::abs(non_normalized.length() - 1.0) > 1.0e-4);
    assert(std::abs(ray.direction.length() - 1.0) < 1.0e-4);

    print_success();
}

void test_plane() {
    print_test_preamble("Plane");

    Plane plane(
        Vector(0.0, 0.0, -10.0),
        Vector(0.0, 0.0, 1.0),
        Color(0),
        TraceType::normal
    );
    Ray ray_straight(
        Vector(0.0),
        Vector(0.0, 0.0, -1.0)
    );
    float t_straight = plane.intersect(&ray_straight);
    Vector dir_straight_reflection = plane.getReflectionsDirection(&ray_straight, t_straight);
    Ray ray_non_straight(
        Vector(0.0),
        Vector(-1.0, 0.0, -1.0)
    );
    float t_non_straight = plane.intersect(&ray_non_straight);
    Vector dir_non_straight_reflection = plane.getReflectionsDirection(&ray_non_straight, t_non_straight);

    Vector vec1 = ray_straight.origin + ray_straight.direction * t_straight;
    // Test intersection points
    assert((ray_straight.origin + ray_straight.direction * t_straight) == plane.point);
    assert((ray_non_straight.origin + ray_non_straight.direction * t_non_straight) == Vector(-10.0, 0.0, -10.0));
    // Test reflection directions
    assert(dir_straight_reflection == ray_straight.direction * -1);
    assert(dir_non_straight_reflection == Vector::normalize(Vector(-1.0, 0.0, 1.0)));

    print_success();
}

void test_sphere() {
    print_test_preamble("Sphere");

    Sphere sphere(
        5.0,
        Vector(0.0, 0.0, -20.0),
        Color(0),
        TraceType::normal
    );
    Ray ray_straight(
        Vector(0.0),
        Vector(0.0, 0.0, -1.0)
    );
    // Find out where to hit the sphere for a right angle reflection
    Vector hit_askew_target_position = sphere.center + Vector::normalize(Vector(1.0, 0.0, 1.0)) * sphere.radius;
    Vector hit_askew_dir =  Vector::normalize(hit_askew_target_position);

    Ray ray_non_straight(
        Vector(hit_askew_target_position.x, 0.0, 0.0),
        Vector(0.0, 0.0, -1.0)
    );

    float t_straight = sphere.intersect(&ray_straight);
    Vector dir_straight_reflection = sphere.getReflectionsDirection(&ray_straight, t_straight);

    float t_non_straight = sphere.intersect(&ray_non_straight);
    Vector dir_non_straight_reflection = sphere.getReflectionsDirection(&ray_non_straight, t_non_straight);
    
    // TODO wtf is happening here
    Vector vec1  = ray_straight.origin + ray_straight.direction * t_straight;
    vec1.print();
    Vector vec2(0.0, 0.0, sphere.center.z + sphere.radius);
    vec2.print();
    float wtf = sphere.center.z + sphere.radius;

    std::cout << sphere.radius << std::endl;
    assert((ray_straight.origin + ray_straight.direction * t_straight) == Vector(0.0, 0.0, sphere.center.z + sphere.radius));
    assert(dir_straight_reflection == Vector(0.0, 0.0, 1.0));
    assert((ray_non_straight.origin + ray_non_straight.direction * t_non_straight) == hit_askew_target_position);
    assert((dir_non_straight_reflection == Vector(1.0, 0.0, 0.0)));

    print_success();
}

int main(int argc, char *argv[]){
    std::cout << "Running test ..." << std::endl;
    test_color();
    test_vector();
    test_ray();
    test_plane();
    test_sphere();
}
