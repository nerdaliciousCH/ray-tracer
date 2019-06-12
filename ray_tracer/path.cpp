#include "path.h"

#include <time.h>

float EPSILON = 1.0e-4; // TODO make this a global

Path::Path(Ray initial_ray, std::vector<Intersectable *> *intersectables, Sphere *light, int max_path_length) :
    intersectables(intersectables),
    initial_ray(initial_ray),
    max_path_length(max_path_length),
    light(light),
    color(Color(0, 0, 0)) {
}

void Path::trace() {
    // Primary ray
    float min_t = std::numeric_limits<float>::max();
    Intersectable *min_i = NULL;
    Ray ray = initial_ray;

    int ray_count = 0;

    for(std::vector<Intersectable *>::iterator it = intersectables->begin(); it != intersectables->end(); ++it){
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
        color = min_i->color;
    }
    ray_count++;

    // Shadow ray and reflection
    if(!(min_i->isLightSource)){
        // Save old hit information
        Vector init_origin = ray.origin;
        Vector init_direction = ray.direction;
        float init_min_t = min_t;
        Intersectable *initial_hit_object = min_i;

        // Get hit position and set ray for Shadow ray
        Vector hit_point = ray.origin + ray.direction * min_t;
        ray.origin = hit_point;
        ray.direction = Vector::normalize(light->center - hit_point);
        Vector new_origin_epsilon = ray.origin + ray.direction * 0.0001;
        ray.origin = new_origin_epsilon;

        // Reset hit info
        min_i = NULL;
        min_t = std::numeric_limits<float>::max();
        for(std::vector<Intersectable *>::iterator it = intersectables->begin(); it != intersectables->end(); ++it){
            float t = (*it)->intersect(ray);
            if (t < min_t){
                min_t = t;
                min_i = *it;
            }
        }
        bool isShadow = !min_i->isLightSource;

        // Reflection
        if(initial_hit_object->isReflective){
            ray_count++;
            Ray old_ray(init_origin, init_direction);
            Vector reflection = initial_hit_object->getReflectionsDirection(old_ray, init_min_t);
            ray.origin = init_origin + init_direction * init_min_t;
            ray.direction = Vector::normalize(reflection);
            ray.origin = ray.origin + ray.direction * 0.0001;

            // Hit another object as perfect reflection.
            min_i = NULL;
            min_t = std::numeric_limits<float>::max();
            for(std::vector<Intersectable *>::iterator it = intersectables->begin(); it != intersectables->end(); ++it){
                float t = (*it)->intersect(ray);
                if (t < min_t){
                    min_t = t;
                    min_i = *it;
                }
            }
            color = min_i->color;
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
