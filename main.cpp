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
int WIDTH = 128;
int HEIGHT = 128;
float BOX_DIM = 2.5;

void ray_trace_function(Camera *camera, std::vector<Intersectable *> *intersectables, Sphere* light, int *color_buffer, int width, int height, int start_index_row, int rows_per_thread, int depth){
	for(int i = start_index_row; i < start_index_row+rows_per_thread; i++){
		for(int j = 0; j < width; j++) {

			unsigned int base = (i*width+j)*3;
			float x = -0.5 + (float)i / (float)width;
			float y = -0.5 + (float)j / (float)height;

			Ray initial_ray(
				camera->getPosition(),
				Vector(y, x, -0.9) // TODO why do I have to flip this?
				// TODO adjust how Z-coord affects FOV
			);

			Path path(
				&initial_ray,
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
}

int main(int argc, char *argv[]) {

	// Get input
	int num_threads = std::stoi(argv[1]);
	int pixel_factor = std::stoi(argv[2]);
	WIDTH *= pixel_factor;
	HEIGHT *= pixel_factor;
	int depth = 4;
	float radius = 0.5;

	// Setup timer
	typedef std::chrono::high_resolution_clock Clock;
	auto time_start = Clock::now();

	Camera *camera = new Camera(
		Vector(0.0),
		Vector(0.0, 1.0, 0.0),
		Vector(0.0, 0.0, -1.0)
	);

	Sphere *light = new Sphere(radius, Vector(-1.0, -BOX_DIM+0.45, -4.5), Color(255, 255, 255), TraceType::light);

	std::vector<Intersectable *> *intersectables = new std::vector<Intersectable *>();

	intersectables->push_back(
		light
	);
	// Wall left
	intersectables->push_back(
		new Plane(Vector(-BOX_DIM, 0.0, 0.0), Vector(1.0, 0.0, 0.0), Color(0, 0, 255), TraceType::normal)
	);
	// Wall right
	intersectables->push_back(
		new Plane(Vector(BOX_DIM, 0.0, 0.0), Vector(-1.0, 0.0, 0.0), Color(255, 0, 0), TraceType::normal)
	);
	// Wall front
	intersectables->push_back(
		new Plane(Vector(0.0, 0.0, -10), Vector(0.0, 0.0, 1.0), Color(255, 255, 255), TraceType::reflective)
	);
	// Wall back
	intersectables->push_back(
		new Plane(Vector(0.0, 0.0, BOX_DIM), Vector(0.0, 0.0, -1.0), Color(150, 150, 150), TraceType::normal)
	);
	// Wall top
	intersectables->push_back(
		new Plane(Vector(0.0, -BOX_DIM, 0.0), Vector(0.0, 1.0, 0.0), Color(255, 150, 255), TraceType::normal)
	);
	// Wall bottom
	intersectables->push_back(
		new Plane(Vector(0.0, BOX_DIM, 0.0), Vector(0.0, -1.0, 0.0), Color(255, 150, 255), TraceType::normal)
	);
	// Red sphere
	intersectables->push_back(
		new Sphere(radius, Vector(-0.5, 1.5, -6.0), Color(255, 0, 0), TraceType::normal)
	);
	// Green sphere
	intersectables->push_back(
		new Sphere(radius, Vector(0.75, 1.5, -5.5), Color(0, 255, 0), TraceType::reflective)
	);

	srand(time(NULL)); // For the rand() function used in stochastic global illumination

	int *color_buffer = (int *)malloc(HEIGHT*WIDTH*3*sizeof(int));

	if (num_threads > 1) {
		if (num_threads > HEIGHT){
			num_threads = HEIGHT;
			std::cout << "Too many threads!" << std::endl;
		}
		std::cout << "Running with " << num_threads << " worker threads" << std::endl;

		std::thread worker_threads[num_threads];
		int rows_per_thread = HEIGHT / num_threads;
		int current_thread_idx = 0;

		for(int i = 0; i < num_threads; i++){
			worker_threads[current_thread_idx] = std::thread(
				&ray_trace_function,
				camera,
				intersectables,
				light,
				color_buffer,
				WIDTH,
				HEIGHT,
				i*rows_per_thread,
				rows_per_thread,
				depth
			);
			current_thread_idx++;
		}

		for(int i = 0; i < num_threads; i++){
			worker_threads[i].join();
		}

	} else {
		std::cout << "Running with 1 thread (main thread)" << std::endl;
		ray_trace_function(
			camera,
			intersectables,
			light,
			color_buffer,
			WIDTH,
			HEIGHT,
			0,
			HEIGHT,
			depth
		);
	}


	auto time_end = Clock::now();
	auto time_spent = duration_cast<duration<double>>(time_end - time_start);
	print_time_spent(time_spent, "Time spent");

	drawbmp("ray-trace.bmp", color_buffer, WIDTH, HEIGHT);

	return 0;
}
