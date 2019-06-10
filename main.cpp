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
int pixel_factor = 30;
int WIDTH = 16*pixel_factor;
int HEIGHT = 16*pixel_factor;
float BOX_DIM = 2.5;

int main(int argc, char *argv[]) {
	// Get input
	float radius = std::stof(argv[1]);
	int depth = std::stoi(argv[2]);
	int samples = std::stoi(argv[3]);

	// Setup timer
	typedef std::chrono::high_resolution_clock Clock;
	auto time_start = Clock::now();

	Camera camera(
		Vector(0.0),
		Vector(0.0, 1.0, 0.0),
		Vector(0.0, 0.0, -1.0)
	);

	Sphere *light = new Sphere(radius, Vector(0.0, -BOX_DIM + 0.45, 1.5), Color(255, 255, 255), true, false);

	std::vector<Intersectable *> intersectables;

	intersectables.push_back(
		light
	);
	// Wall left
	intersectables.push_back(
		new Plane(Vector(-BOX_DIM, 0.0, 0.0), Vector(1.0, 0.0, 0.0), Color(0, 0, 255), false, false)
	);
	// Wall right
	intersectables.push_back(
		new Plane(Vector(BOX_DIM, 0.0, 0.0), Vector(-1.0, 0.0, 0.0), Color(255, 0, 0), false, false)
	);
	// Wall front
	intersectables.push_back(
		new Plane(Vector(0.0, 0.0, -10), Vector(0.0, 0.0, 1.0), Color(255, 255, 255), false, true)
	);
	// Wall back
	intersectables.push_back(
		new Plane(Vector(0.0, 0.0, BOX_DIM), Vector(0.0, 0.0, -1.0), Color(150, 150, 150), false, false)
	);
	// Wall top
	intersectables.push_back(
		new Plane(Vector(0.0, -BOX_DIM, 0.0), Vector(0.0, -1.0, 0.0), Color(150, 150, 150), false, false)
	);
	// Wall bottom
	intersectables.push_back(
		new Plane(Vector(0.0, BOX_DIM, 0.0), Vector(0.0, 1.0, 0.0), Color(150, 150, 150), false, false)
	);
	// Red sphere
	intersectables.push_back(
		new Sphere(radius, Vector(0.0, 1.0, -5.0), Color(255, 0, 0), false, false)
	);
	// Green sphere
	intersectables.push_back(
		new Sphere(radius, Vector(0.75, 1.0, -3.4), Color(0, 255, 0), false, true)
	);

	srand(time(NULL));

	int *color_buffer = (int *)malloc(HEIGHT*WIDTH*3*sizeof(int));

	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++) {

			unsigned int base = (i*WIDTH+j)*3;
			float x = -0.5 + (float)i / (float)WIDTH;
			float y = -0.5 + (float)j / (float)HEIGHT;

			Ray initial_ray(
				camera.getPosition(),
				Vector(y, x, -1.0) // TODO why do I have to flip this?
				// TODO adjust how Z-coord affects FOV
			);

			Path path(
				initial_ray,
				intersectables,
				light,
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
