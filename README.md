# Rei_Tracer
miniRT project from 42 (evangelion reference)

*This project has been created as part of the 42 curriculum by gmu and sabruma*

### Description

Ray tracing is a render tecnique by shooting a ray. In the image is show how it works, the camera and the window of pixels rappresenting how it should work. When we cast a ray whe ask how much light is reflected to compute the pixel's color.

![image](img.png)

The animated film industry rely heavily on ray tracing, not only for visual effect, a lot of film were fully rendered using ray tracing tecniques, for example Frozen and Ice Ace.

Nowdays computer whith a good graphic card can render a fully ray-traced videogames like Cyberpunk 2077.

This project help us to understand the apperence of the world around us. Because we simulate how lights and color works when we see things.

### Instructions

to compile:

```terminal
make mlx && make
```

to execute:
```terminal
./miniRT test.rt
```
to test and benchmark our code:
```make test``` or ```make bench```

### Resources

Thanks a lot to:
https://www.scratchapixel.com/

https://raytracing.github.io/books/RayTracingInOneWeekend.html

The Ray Tracer Challenge-Pragmatic Bookshelf (2019) - Jamis Buck 

Linear Algebra and Its Applications - Gilbert Strang

Linear Albegra Done Right - Sheldon Axler

3D Math Primer for Graphics and Game Development - F.Dunn, I.Parberry

#### AI usage (mainly Deepseek):

- Some parser functions
- Theory study and some clarification
- Some cursed debugging when really stuck
- Build system structure
- Header organization and enforcing of best practices
- Research of common utilities and features in CGI

## Other info
For faster (parallel) builds do:
```export MAKEFLAGS="-j$(nproc)"```.

By default ```make``` for your current session will use these flags.
Sometimes this causes ```make re``` to fail: worry not, just retry one more time!

## Technical specs

This project uses solely the ray-tracing rendering technique (Keija's algorithm without recursion).
The project is organizaed in a modular fashion, subdivided into:
- ```libc``` aka ```libft``` for common lowlevel utilities and string manipulation
- ```math_engine```, which handles the vector & matrix calculus, as well as geometric entities required by the subject (spheres, planes, cylinder + lights and camera).
- ```minirt```, which is a wrapper around the engine and handles data flow, the MiniLibX API and the rendering phase.
- Modular build system: the master Makefile inside the project root builds all the required dependencies.
- ```gen_spheres.py <n_spheres>```: a script to generate random spheres