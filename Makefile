COMPILER = g++
FLAGS = -g -O3

program: main.o draw_bmp.o utility_functions.o camera.o color.o vector.o plane.o sphere.o ray.o path.o phong.o
	$(COMPILER) -pthread $(FLAGS) main.o draw_bmp.o utility_functions.o camera.o color.o vector.o plane.o sphere.o ray.o path.o phong.o -o program
	
main.o: main.cpp
	$(COMPILER) $(FLAGS) -c main.cpp

draw_bmp.o: helpers/draw_bmp.c helpers/draw_bmp.h
	$(COMPILER) $(FLAGS) -c helpers/draw_bmp.c

utility_functions.o: helpers/utility_functions.cpp helpers/utility_functions.h
	$(COMPILER) $(FLAGS) -c helpers/utility_functions.cpp

camera.o: camera/camera.cpp camera/camera.h
	$(COMPILER) $(FLAGS) -c camera/camera.cpp

color.o: color/color.cpp color/color.h
	$(COMPILER) $(FLAGS) -c color/color.cpp

vector.o: math/vector.cpp math/vector.h
	$(COMPILER) $(FLAGS) -c math/vector.cpp

plane.o: geometry/plane.cpp geometry/plane.h
	$(COMPILER) $(FLAGS) -c geometry/plane.cpp

sphere.o: geometry/sphere.cpp geometry/sphere.h
	$(COMPILER) $(FLAGS) -c geometry/sphere.cpp

ray.o: geometry/ray.cpp geometry/ray.h
	$(COMPILER) $(FLAGS) -c geometry/ray.cpp

path.o: ray_tracer/path.cpp ray_tracer/path.h
	$(COMPILER) $(FLAGS) -c ray_tracer/path.cpp

phong.o: lighting/phong.cpp lighting/phong.h
	$(COMPILER) $(FLAGS) -c lighting/phong.cpp
