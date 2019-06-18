#include "path.h"

#include <time.h>

float EPSILON = 1.0e-3; // TODO make this a global

Path::Path(Ray *initial_ray, std::vector<Intersectable *> *intersectables, Sphere *light, int max_path_length, int random_samples) :
    intersectables(intersectables),
    initial_ray(initial_ray),
    max_path_length(max_path_length),
    random_samples(random_samples),
    light(light),
    color(Color(0)) {
}

void Path::get_shadow_ray(Ray *ray_in, Hit* hit_in, Sphere* light_in, Ray *ray_out){
    Vector hit_point = ray_in->origin + ray_in->direction * hit_in->t;
    ray_out->direction = Vector::normalize(light_in->center - hit_point);
    // Step away a bit from itersection point to not self intersect due to nuemerical issues
    ray_out->origin = hit_point + ray_out->direction * EPSILON;
    hit_in->ray = ray_in;
}

void Path::get_reflection_ray(Ray *ray_in, Hit* hit_in, Ray *ray_out) {
    Vector hit_point = ray_in->origin + ray_in->direction * hit_in->t;
    ray_out->direction = hit_in->object->getReflectionsDirection(ray_in, hit_in->t);
    // Step away a bit from itersection point to not self intersect due to nuemerical issues
    ray_out->origin = hit_point + ray_out->direction * EPSILON;
    hit_in->ray = ray_in;
}

void Path::get_stochastic_hemisphere_ray(Ray *ray_in, Hit* hit_in, Ray *ray_out){
    Vector hit_point = ray_in->origin + ray_in->direction * hit_in->t;
    Vector normal_direction = hit_in->object->getNormal(hit_point);

    // Get random point on hemisphere
    // Radians [0, 2*PI]
    float r1 = 2*M_PI*static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    // Radians [0, PI/2]
    float r2 = M_PI*static_cast <float> (rand()) / static_cast <float> (RAND_MAX) / 2;

    float x = cos(r1) * sin(r2);
    float y = sin(r1) * sin(r2);
    float z = cos(r2);

    // Base transform to hemisphere defined by surface normal vector at hit point
    // Gram Schmidt orthogonalization
    Vector unit_x(1.0, 1.0, 1.0);
    Vector w = normal_direction;
    Vector u = Vector::normalize(Vector::cross(Vector::normalize(unit_x), w));
    Vector v = Vector::normalize(Vector::cross(w, u));
    // Transform Vector to new coordinates
    Vector random_direction = Vector::normalize(u*x+v*y+w*z);

    ray_out->origin = hit_point + random_direction * EPSILON;
    ray_out->direction = random_direction;
    hit_in->ray = ray_in;
}

void Path::find_intersection(Ray *ray, Hit *hit){
    hit->object = NULL;
    hit->t = std::numeric_limits<float>::max();
    for(std::vector<Intersectable *>::iterator it = intersectables->begin(); it != intersectables->end(); ++it){
        float t = (*it)->intersect(ray);
        if (t < hit->t){
            hit->t = t;
            hit->object = *it;
        }
    }
    hit->ray = ray;
}

void Path::trace() {
    // Primary ray
    Ray* ray = initial_ray;
    Ray out_ray;

    Hit hit;
    Hit primary_hit;
    
    // Primary ray
    find_intersection(ray, &primary_hit);
    if(primary_hit.object == NULL){
        // No hit (pure darkness), so we abort here
        return;
    } else {
        // We hit something
        if(primary_hit.object->type != TraceType::light){
            Color col(0);
            Ray new_ray;
            Hit new_hit;
            Color primary_color = PhongModel::calculate(initial_ray, &primary_hit, &(light->center), &(light->color));
            for(int i = 0; i < random_samples; i++) {
                Path::get_stochastic_hemisphere_ray(initial_ray, &primary_hit, &new_ray);
                find_intersection(&new_ray, &new_hit);
                float fac = 1.0/(1.0+new_hit.t);
                color = color + new_hit.object->color * fac;
            }
            color /= random_samples;
            color = color / 2 + primary_color / 2;
        }else{
            color = primary_hit.object->color;
        }
    }

    // Shadow ray
    if(primary_hit.object->type != TraceType::light){
        // Reset hit info
        get_shadow_ray(initial_ray, &primary_hit, light, &out_ray);
        find_intersection(&out_ray, &hit);
        bool isShadow = hit.object->type != TraceType::light;
        if (isShadow) {
            color /= 2.5;
        }
    }
}

Color Path::getColor() {
    return color;
}
