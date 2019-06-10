#include "path.h"

#include <limits>

Path::Path(Ray initial_ray, std::vector<Intersectable *> intersectables, Sphere *light, int max_path_length) :
    intersectables(intersectables),
    initial_ray(initial_ray),
    light(light),
    max_path_length(max_path_length),
    color(Color(0, 0, 0)) {
}

void Path::trace() {

    // std::cout << "TRACING RAY\n-------------------------\n";

    float min_t = std::numeric_limits<float>::max();
    Intersectable *min_i = NULL;
    Vector new_pos(0.0);
    Vector new_dir(0.0);
    Ray ray = initial_ray;

    for(int i = 0; i < max_path_length; i++) {
        // Find intersections with regulra objects
        for(std::vector<Intersectable *>::iterator it = intersectables.begin(); it != intersectables.end(); ++it){
            float t = (*it)->intersect(ray);
            if (t < min_t){
                min_t = t;
                min_i = *it;
            }
        }

        // Find intersection with lightbulb
        float t_light = light->intersect(ray);
        if (t_light < min_t) {
            min_t = t_light;
            min_i = light;
        }

        if (min_i == NULL && path_length == 0){
            // No hit here on initial ray. Darkness.
            return;
        }
        path_length++;
        if(min_i == NULL){
            // No hit (pure darkness), so we abort and return color so far
            break;
        } else {
            // We hit something
            // Get hit object's color
            color.r += min_i->color.r;
            color.g += min_i->color.g;
            color.b += min_i->color.b;
            Vector reflection = min_i->getReflectionsDirection(ray, min_t);
            new_pos = ray.origin + ray.direction * min_t;
            new_dir = Vector::normalize(reflection);
            ray.origin = new_pos;
            ray.direction = new_dir;
        }

    }
    // TODO shadow ray. Go to light. see if somethin intersects

    // Return corrected color
    if (path_length > 0){
        color.r = (int) ((float)color.r / max_path_length);
        color.g = (int) ((float)color.g / max_path_length);
        color.b = (int) ((float)color.b / max_path_length);
    }
}

void Path::setColor(Color color) {

}

Color Path::getColor() {
    return color;
}
