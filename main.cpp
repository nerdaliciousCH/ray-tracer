#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "helpers/utility_functions.h"
#include "helpers/draw_bmp.h"
#include "geometry/intersectable.h"
#include "geometry/plane.h"
#include "geometry/sphere.h"
#include "geometry/ray.h"
#include "color/color.h"
#include "camera/camera.h"
#include "math/vector.h"
#include "ray_tracer/path.h"

using namespace std::chrono;

// Globals
int pixel_factor = 20;
int WIDTH = 16*pixel_factor;
int HEIGHT = 16*pixel_factor;
float BOX_DIM = 0.5;

int main(int argc, char *argv[]) {
	// Get input
	float radius = (float)std::stoi(argv[1]);
	int depth = std::stoi(argv[2]);
	int samples = std::stoi(argv[3]);

	// Setup timer
	typedef std::chrono::high_resolution_clock Clock;
	auto time_start = Clock::now();

	Camera camera(
		Vector(2.0, 0.0, 0.0),
		Vector(0.0, 1.0, 0.0),
		Vector(0.0, 0.0, -1.0)
	);

	Sphere lightBulb(radius, Vector(5.0, 2.5, -20.0), Color(255, 255, 255));

	std::vector<Intersectable *> intersectables;

	float radius_wall = 1000.0;
	// Wall left
	intersectables.push_back(
		new Plane(Vector(-BOX_DIM, 0.0, 0.0), Vector(1.0, 0.0, 0.0), Color(0, 0, 255))
	);
	// Wall right
	intersectables.push_back(
		new Plane(Vector(BOX_DIM, 0.0, 0.0), Vector(-1.0, 0.0, 0.0), Color(255, 0, 0))
	);
	// // Wall front
	// intersectables.push_back(
	// 	new Plane(Vector(0.0, 0.0, -BOX_DIM), Vector(0.0, 0.0, 1.0), Color(0, 255, 255))
	// );
	// // Wall back
	// intersectables.push_back(
	// 	new Plane(Vector(0.0, 0.0, BOX_DIM), Vector(0.0, 0.0, -1.0), Color(255, 255, 0))
	// );
	// Wall top
	intersectables.push_back(
		new Plane(Vector(0.0, BOX_DIM, 0.0), Vector(0.0, -1.0, 0.0), Color(0, 255, 0))
	);
	// Wall bottom
	intersectables.push_back(
		new Plane(Vector(0.0, -BOX_DIM, 0.0), Vector(0.0, 1.0, 0.0), Color(255, 0, 255))
	);

	// // Red sphere
	// intersectables.push_back(
	// 	new Sphere(radius, Vector(0.0, 0.0, -20.0), Color(255, 0, 0))
	// 	);
	// // Green sphere
	// intersectables.push_back(
	// 	new Sphere(radius, Vector(0.0, 3.0, -20.0), Color(0, 255, 0))
	// 	);

	srand(time(NULL));

	int *color_buffer = (int *)malloc(HEIGHT*WIDTH*3*sizeof(int));

	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++) {

			unsigned int base = (i*WIDTH+j)*3;
			float x = -0.5 + (float)i / (float)WIDTH;
			float y = -0.5 + (float)j / (float)HEIGHT;

			Ray initial_ray(
				camera.getPosition(),
				Vector::normalize(Vector(y, x, -2.0)) // TODO why do I have to flip this?
			);

			Path path(
				initial_ray,
				intersectables,
				lightBulb,
				depth
			);
			path.trace();

			Color final_color = path.getColor();
			color_buffer[base] = final_color.r;
			color_buffer[base + 1] = final_color.g;
			color_buffer[base + 2] = final_color.b;
		}
	}

	auto time_end = Clock::now();
	auto time_spent = duration_cast<duration<double>>(time_end - time_start);
	print_time_spent(time_spent, "Time spent");

	drawbmp("ray-trace.bmp", color_buffer, WIDTH, HEIGHT);

	return 0;
}
