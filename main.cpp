#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "helpers/utility_functions.h"
#include "helpers/draw_bmp.h"
#include "geometry/intersectable.h"
#include "geometry/sphere.h"
#include "geometry/cube.h"
#include "geometry/ray.h"
#include "color/color.h"
#include "camera/camera.h"
#include "math/vector.h"

using namespace std::chrono;

// Globals
int pixel_factor = 40;
int WIDTH = 16*pixel_factor;
int HEIGHT = 9*pixel_factor;

int main(int argc, char *argv[]) {
	// Get input
	float radius = (float)std::stoi(argv[1]);

	// Setup timer
	typedef std::chrono::high_resolution_clock Clock;
	auto time_start = Clock::now();

	Camera camera(
		Vector(10.0, 0.0, 0.0),
		Vector(0.0, 1.0, 0.0),
		Vector(0.0, 0.0, -1.0)
	);

	std::vector<Intersectable *> intersectables;
	intersectables.push_back(
		new Cube(
			Vector(1.0, 0.0, -20.0),
			0.1, 0.1, 0.1, Color(0, 0, 255)
		)
	);
	intersectables.push_back(
		new Sphere(radius, Vector(0.0, 0.0, -20.0), Color(255, 0, 0))
		);
	intersectables.push_back(
		new Sphere(radius, Vector(0.0, 5.0, -20.0), Color(0, 255, 0))
		);

	srand(time(NULL));

	int *color_buffer = (int *)malloc(HEIGHT*WIDTH*3*sizeof(int));

	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++) {

			unsigned int base = (i*WIDTH+j)*3;

			float x = -0.5 + (float)i / (float)WIDTH;
			float y = -0.5 + (float)j / (float)HEIGHT;
			Ray initial_ray(
				Vector(0.0, 0.0, 0.0),
				Vector(x, y, -1.0)
			);
			for(std::vector<Intersectable *>::iterator it = intersectables.begin(); it != intersectables.end(); ++it){
				Vector res = (*it)->intersect(initial_ray);
				if(res.x > 0){
					color_buffer[base] = (*it)->color.r;
					color_buffer[base + 1] = (*it)->color.g;
					color_buffer[base + 2] = (*it)->color.b;
				}

			}
		}
	}

	auto time_end = Clock::now();
	auto time_spent = duration_cast<duration<double>>(time_end - time_start);
	print_time_spent(time_spent, "Time spent");

	drawbmp("ray-trace.bmp", color_buffer, WIDTH, HEIGHT);

	return 0;
}
