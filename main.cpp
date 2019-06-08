#include <iostream>
#include <iomanip>
#include <string>

#include "helpers/utility_functions.h"
#include "helpers/draw_bmp.h"
#include "geometry/sphere.h"
#include "geometry/ray.h"
#include "color/color.h"
#include "camera/camera.h"

using namespace std::chrono;

int WIDTH = 320;
int HEIGHT = 240;

int main(int argc, char *argv[]) {

	typedef std::chrono::high_resolution_clock Clock;
	auto t1 = Clock::now();

	Camera camera(
		Vector(10.0, 0.0, 0.0),
		Vector(0.0, 1.0, 0.0),
		Vector(0.0, 0.0, -1.0)
	);

	// Sphere wall_back();
	// Sphere wall_left();
	// Sphere wall_right();
	// Sphere wall_front();
	Sphere sphere_left(0.5, Vector(1.0, 1.0, -10.0), Color(255, 0, 0));
	Sphere sphere_right(0.5, Vector(-1.0, 1.0, -10.0), Color(0, 255, 0));

	for(int i = 0; i < WIDTH; i++){
		for(int j = 0; j < HEIGHT; j++) {
			float x = -0.5 + (float)i / (float)WIDTH;
			float y = -0.5 + (float)j / (float)HEIGHT;
			Ray ray(
				Vector(0.0, 0.0, 0.0),
				Vector(x, y, -1.0)
			);
			ray.print();

		}
	}

	auto t2 = Clock::now();
	auto time_spent = duration_cast<duration<double>>(t2 - t1);
	print_time_spent(time_spent, "right");

	int *arr = (int *)malloc(HEIGHT*WIDTH*3*sizeof(int));
	for(int i = 0; i < HEIGHT; i++) {
		for(int j = 0; j < WIDTH*3; j+=3) {
			unsigned int base = i*HEIGHT+j;
			arr[base] = 0;
			arr[base + 1] = 255;
			arr[base + 2] = 0;
		}
	}

	drawbmp("test.bmp", arr, WIDTH, HEIGHT);

	return 0;
}
