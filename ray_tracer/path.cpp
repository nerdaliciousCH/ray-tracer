#include "path.h"

#include <time.h>

float EPSILON = 1.0e-3; // TODO make this a global

Path::Path(Ray *initial_ray, std::vector<Intersectable *> *intersectables, Sphere *light, int max_path_length) :
    intersectables(intersectables),
    initial_ray(initial_ray),
    max_path_length(max_path_length),
    light(light),
    color(Color(0, 0, 0)) {
}
void Path::get_shadow_ray(Ray *ray, Hit* hit, Ray *out){
    Vector hit_point = ray->origin + ray->direction * hit->t;
    out->direction = Vector::normalize(light->center - hit_point);
    // Step away a bit from itersection point to not self intersect due to nuemerical issues
    out->origin = hit_point + out->direction * EPSILON;
}

void Path::get_reflection_ray(Ray *ray, Hit* hit, Ray *out) {
    Vector hit_point = ray->origin + ray->direction * hit->t;
    out->direction = hit->object->getReflectionsDirection(ray, hit->t);
    // Step away a bit from itersection point to not self intersect due to nuemerical issues
    out->origin = hit_point + out->direction * EPSILON;
}

void Path::get_stochastic_hemisphere_ray(Ray *ray, Hit* hit, Ray *out){
    Vector hit_point = ray->origin + ray->origin * hit->t;
    Vector normal_direction = hit->object->getNormal(hit_point);
    // TODO
    Vector random_direction = Vector::normalize(random_direction);
    out->origin = hit_point + normal_direction * EPSILON;
    out->direction = random_direction;
}

void Path::trace_ray(Ray *ray, Hit *hit){
    hit->object = NULL;
    hit->t = std::numeric_limits<float>::max();
    for(std::vector<Intersectable *>::iterator it = intersectables->begin(); it != intersectables->end(); ++it){
        float t = (*it)->intersect(ray);
        if (t < hit->t){
            hit->t = t;
            hit->object = *it;
        }
    }
}

void Path::trace() {
    // Primary ray
    float min_t = std::numeric_limits<float>::max();
    Intersectable *min_i = NULL;
    Ray* ray = initial_ray;
    Ray out_ray;

    int ray_count = 0;
    Hit hit;
    Hit primary_hit;

    // TODO correct recursion at the end, when verified, that the partial ray functions are all correct

    // Primary ray
    trace_ray(ray, &primary_hit);
    if(primary_hit.object == NULL){
        // No hit (pure darkness), so we abort here
        return;
    } else {
        // We hit something
        // Get hit object's color
        color = primary_hit.object->color;
    }
    ray_count++;

    // Shadow ray and reflection
    if(primary_hit.object->type != TraceType::light){

        // Reset hit info
        get_shadow_ray(initial_ray, &primary_hit, &out_ray);
        trace_ray(&out_ray, &hit);
        bool isShadow = hit.object->type != TraceType::light;
        if (isShadow) {
            ray_count *= 5;
        }
    }

    // Reflection
    if(primary_hit.object->type == TraceType::reflective){
        ray_count++;
        // Hit another object as perfect reflection.
        get_reflection_ray(initial_ray, &primary_hit, &out_ray);
        trace_ray(&out_ray, &hit);
        color = hit.object->color;
    }

    // // Stochastic light
    // for(int i = 0; i < max_path_length; i++){
    //     get_stochastic_hemisphere_ray(initial_ray, &primary_hit, &out_ray);
    //     trace_ray(&out_ray, &hit);
    //     if (hit.object != NULL){
    //         color = color + hit.object->color;
    //         ray_count++;
    //     }
    // }

    // Normalize color
    color /= ray_count;
}

void Path::setColor(Color color) {

}

Color Path::getColor() {
    return color;
}
