# A simple C++ CPU ray tracer 

The purpose of this project is to learn C++ with a focus on writing fast code as well as advancing my simple knowledge of ray tracing from my time as Undergraduate at ETH Zürich.

Why a ray tracer?
First of all: It's fun!
It is also a small size goal but nevertheless there are so many different aspects to it, which means that there is always something that can be improved or added to it. Hence there is a natural story line for what is to be done next.

## Current visual state
Global illumination via random hemisphere sampling 

![Render Global Illumination](renders/phong_and_global_ilumination_500_samples.bmp)

## TODOs

- recursive path tracing with reflections and shadows
- refraction
- glow/emissive surfaces instead of pure white light
- acceleration structure (Bounding Volume Hierarchy)
- CUDA version