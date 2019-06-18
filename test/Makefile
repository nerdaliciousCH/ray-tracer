test: test.o draw_bmp.o utility_functions.o camera.o color.o vector.o plane.o sphere.o ray.o phong.o path.o
	g++ -g test.o draw_bmp.o utility_functions.o camera.o color.o vector.o plane.o sphere.o ray.o phong.o path.o -o test

test.o: test.cpp
	g++ -g -c test.cpp

draw_bmp.o: ../helpers/draw_bmp.c ../helpers/draw_bmp.h
	g++ -g -c ../helpers/draw_bmp.c

utility_functions.o: ../helpers/utility_functions.cpp ../helpers/utility_functions.h
	g++ -g -c ../helpers/utility_functions.cpp

camera.o: ../camera/camera.cpp ../camera/camera.h
	g++ -g -c ../camera/camera.cpp

color.o: ../color/color.cpp ../color/color.h
	g++ -g -c ../color/color.cpp

vector.o: ../math/vector.cpp ../math/vector.h
	g++ -g -c ../math/vector.cpp

plane.o: ../geometry/plane.cpp ../geometry/plane.h
	g++ -g -c ../geometry/plane.cpp

sphere.o: ../geometry/sphere.cpp ../geometry/sphere.h
	g++ -g -c ../geometry/sphere.cpp

ray.o: ../geometry/ray.cpp ../geometry/ray.h
	g++ -g -c ../geometry/ray.cpp

phong.o: ../lighting/phong.cpp ../lighting/phong.h
	g++ -g -c ../lighting/phong.cpp

path.o: ../ray_tracer/path.cpp ../ray_tracer/path.h
	g++ -g -c ../ray_tracer/path.cpp
