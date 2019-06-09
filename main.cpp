#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <time.h>

#include "helpers/utility_functions.h"
#include "helpers/draw_bmp.h"
#include "geometry/sphere.h"
#include "geometry/ray.h"
#include "color/color.h"
#include "camera/camera.h"
#include "math/vector.h"

using namespace std::chrono;
int fac = 60;
int WIDTH = 16*fac;
int HEIGHT = 9*fac;

int main(int argc, char *argv[]) {

	float radius = (float)std::stoi(argv[1]);
	std::cout << radius;
	typedef std::chrono::high_resolution_clock Clock;
	auto t1 = Clock::now();
	Vector v1(0.1, 0.2, 0.3);
	Vector v2(0.3, 0.2, 0.6666);
	// TODO remove above

	Camera camera(
		Vector(10.0, 0.0, 0.0),
		Vector(0.0, 1.0, 0.0),
		Vector(0.0, 0.0, -1.0)
	);

	// Sphere wall_back();
	// Sphere wall_left();
	// Sphere wall_right();
	// Sphere wall_front();
	Sphere sphere_left(radius, Vector(0.0, 0.0, -20.0), Color(255, 0, 0));
	Sphere sphere_right(radius, Vector(0.0, 5.0, -20.0), Color(0, 255, 0));

	srand(time(NULL));

	int *arr = (int *)malloc(HEIGHT*WIDTH*3*sizeof(int));

	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++) {

			unsigned int base = (i*WIDTH+j)*3;
			arr[base] = 0;
			arr[base + 1] = 0;
			arr[base + 2] = 0;

			float x = -0.5 + (float)i / (float)WIDTH;
			float y = -0.5 + (float)j / (float)HEIGHT;
			Ray ray(
				Vector(0.0, 0.0, 0.0),
				Vector(x, y, -1.0)
			);
			float r2 = sphere_left.radius * sphere_left.radius;
			Vector v = sphere_left.center - ray.origin;
			// A
			float d2 = Vector::dot(ray.direction, ray.direction);
			// B
			float twice_vd = Vector::dot(v, ray.direction) * 2;
			// C
			float v_minus_c = Vector::dot(v, v) - r2;

			float discriminant = twice_vd * twice_vd - 4 * d2 * v_minus_c;

			if(discriminant > 0){
				// std::cout << "Two solutions" << std::endl;
				arr[base] = 0;
				arr[base + 1] = 255;
				arr[base + 2] = 0;
			}
		}
	}

	auto t2 = Clock::now();
	auto time_spent = duration_cast<duration<double>>(t2 - t1);
	print_time_spent(time_spent, "right");

	std::cout << arr << std::endl;

	drawbmp("ray-trace.bmp", arr, WIDTH, HEIGHT);

	return 0;
}
