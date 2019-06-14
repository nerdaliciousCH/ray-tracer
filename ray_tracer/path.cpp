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
Ray* Path::get_shadow_ray(Ray *ray, Hit* hit){
    return NULL;
}

Ray* Path::get_reflection_ray(Ray *ray, Hit* hit) {
    return NULL;
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

    int ray_count = 0;
    Hit hit;
    Hit primary_hit;

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
    if(!(primary_hit.object->type == TraceType::light)){
        // Save old hit information
        Vector init_origin = initial_ray->origin;
        Vector init_direction = initial_ray->direction;
        float init_min_t = primary_hit.t;
        Intersectable *initial_hit_object = primary_hit.object;

        // Get hit position and set ray for Shadow ray
        Vector hit_point = ray->origin + ray->direction * primary_hit.t;
        ray->origin = hit_point;
        ray->direction = Vector::normalize(light->center - hit_point);
        Vector new_origin_epsilon = ray->origin + ray->direction * EPSILON;
        ray->origin = new_origin_epsilon;

        // Reset hit info
        trace_ray(ray, &hit);
        bool isShadow = hit.object->type != TraceType::light;

        // Reflection
        if(initial_hit_object->type == TraceType::reflective){
            ray_count++;
            Ray old_ray(init_origin, init_direction);
            Vector reflection = initial_hit_object->getReflectionsDirection(&old_ray, init_min_t);
            ray->origin = init_origin + init_direction * init_min_t;
            ray->direction = Vector::normalize(reflection);
            ray->origin = ray->origin + ray->direction * EPSILON;

            // Hit another object as perfect reflection.
            trace_ray(ray, &hit);
            color = hit.object->color;
        } else {
            // // Stochastic light
            // for (int i = 0; i < 1; i++){
            //     Vector p = init_origin + init_direction * init_min_t;
            //     Vector n = initial_hit_object->getNormal(p);
            //     p = p + n * 0.0001;
            //     // std::srand(time(NULL));
            //     Vector da_dir(
            //         n.x * std::rand(),
            //         n.y * std::rand(),
            //         n.z * std::rand()
            //     );
            //
            //     da_dir = Vector::normalize(da_dir);
            //
            //     Ray da_ray(p, da_dir);
            //
            //     min_i = NULL;
            //     min_t = std::numeric_limits<float>::max();
            //     for(std::vector<Intersectable *>::iterator it = intersectables->begin(); it != intersectables->end(); ++it){
            //         float t = (*it)->intersect(da_ray);
            //         if (t < min_t){
            //             min_t = t;
            //             min_i = *it;
            //         }
            //     }
            //     if (min_i != NULL){
            //         color = color + min_i->color;
            //         ray_count++;
            //     }
            //
            // }
        }
        if (isShadow) {
            ray_count *= 5;
        }
    }

    // Normalize color
    // color /= ray_count;
    color.r = (int) ((float)color.r / ray_count);
    color.g = (int) ((float)color.g / ray_count);
    color.b = (int) ((float)color.b / ray_count);

}

void Path::setColor(Color color) {

}

Color Path::getColor() {
    return color;
}
