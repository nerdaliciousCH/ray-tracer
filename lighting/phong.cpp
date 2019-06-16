#include "phong.h"
#include <iostream>

Color PhongModel::calculate(Ray* camera_ray, Hit* hit, Vector* light_position, Color* light_color){
    Color phong_color(0);
    Vector hit_point = hit->ray->origin + hit->ray->direction * hit->t;
    Vector surface_normal = hit->object->getNormal(hit_point);
    Vector light_dir = Vector::normalize(*light_position - hit_point);
    Vector light_reflection = Vector::normalize(light_dir - surface_normal * 2 * Vector::dot(light_dir, surface_normal));

    float specular_exponent = 32;
    // Ambient
    // TODO this could be calculate by global illumination
    // Color ambient = *light_color * 0.1;
    Color ambient = Color(0);

    // Diffuse
    float diffuse_coefficient = Vector::dot(light_dir, surface_normal);

    // Specular
    float specular_dot = Vector::dot(
        camera_ray->direction,
        light_reflection
    );
    float specular_coefficient = specular_dot >= 0.0 ? std::pow(
        specular_dot,
        specular_exponent
    ) : 0.0; // TODO this can also be calculated as recursive ray color

    phong_color =  ambient + hit->object->color * (diffuse_coefficient + specular_coefficient);

    return phong_color;
}
