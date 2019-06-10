#include "path.h"

#include <limits>

float EPSILON = 1.0e-4;

Path::Path(Ray initial_ray, std::vector<Intersectable *> intersectables, Sphere *light, int max_path_length) :
    intersectables(intersectables),
    initial_ray(initial_ray),
    max_path_length(max_path_length),
    light(light),
    color(Color(0, 0, 0)) {
}

void Path::trace() {

    /* TODO
    start with primary ray
    then evaluate shadow ray (add light color or black to primary ray color)
    AND evaluate reflective ray (for reflective surface)
    AND shoot stochastic ambient rays (for ambient light) with max_depth
    */

    // Primary ray
    float min_t = std::numeric_limits<float>::max();
    Intersectable *min_i = NULL;
    Vector new_pos(0.0);
    Vector new_dir(0.0);
    Ray ray = initial_ray;

    int ray_count = 0;

    for(std::vector<Intersectable *>::iterator it = intersectables.begin(); it != intersectables.end(); ++it){
        float t = (*it)->intersect(ray);
        if (t < min_t){
            min_t = t;
            min_i = *it;
        }
    }
    if(min_i == NULL){
        // No hit (pure darkness), so we abort here
        return;
    } else {
        // We hit something
        // Get hit object's color
        color.r = min_i->color.r;
        color.g = min_i->color.g;
        color.b = min_i->color.b;
    }
    ray_count++;

    // Shadow ray and reflection
    if(!(min_i->isLightSource)){
        // Get hit position
        Vector init_origin = ray.origin;
        Vector init_direction = ray.direction;
        float init_min_t = min_t;
        Intersectable *initial_hit_object = min_i;
        Vector hit_point = ray.origin + ray.direction * min_t;
        ray.origin = hit_point;
        ray.direction = Vector::normalize(light->center - hit_point);
        Vector new_origin_epsilon = ray.origin + ray.direction * 0.0001;
        ray.origin = new_origin_epsilon;
        min_i = NULL;
        min_t = std::numeric_limits<float>::max();
        for(std::vector<Intersectable *>::iterator it = intersectables.begin(); it != intersectables.end(); ++it){
            float t = (*it)->intersect(ray);
            if (t < min_t){
                min_t = t;
                min_i = *it;
            }
        }
        bool isShadow = !min_i->isLightSource;

        // // Reflectionnnn
        // if(min_i->isReflective){
        //     Vector reflection = initial_hit_object->getReflectionsDirection(ray, init_min_t);
        //     ray.origin = init_origin + init_direction * init_min_t;
        //     ray.direction = Vector::normalize(reflection);
        //     min_i = NULL;
        //     min_t = std::numeric_limits<float>::max();
        //     for(std::vector<Intersectable *>::iterator it = intersectables.begin(); it != intersectables.end(); ++it){
        //         float t = (*it)->intersect(ray);
        //         if (t < min_t){
        //             min_t = t;
        //             min_i = *it;
        //         }
        //     }
        //     color.r += min_i->color.r;
        //     color.g += min_i->color.g;
        //     color.b += min_i->color.b;
        // }
        if (isShadow) {
            ray_count *= 5;
        }
    }

    // Normalize color
    color.r = (int) ((float)color.r / ray_count);
    color.g = (int) ((float)color.g / ray_count);
    color.b = (int) ((float)color.b / ray_count);

}

void Path::setColor(Color color) {

}

Color Path::getColor() {
    return color;
}
