# manual_shading_demo
Demonstration of manual shading in OpenGL using C++

Based on manual_shading branch https://github.com/borna-x86/lab4_irg, a solution to a part of the fourth lab excercise for https://www.fer.unizg.hr/predmet/irg.

**Demonstrates manually computing lighting in OpenGL (legacy) and C++ project structure and code style I usually use for small projects.**

Depends on freeglut and GLM, and can be built with Visual Studio 2017/2019 Enterprise.


#### Running

A .obj filename can be specified as a commandline argument, otherwise teddy.obj is rendered.
Once the object is rendered use 'l', 'r' keypresses to rotate, 'g' for smooth shading & 'k' for flat shading.

#### "Important" features
Manual definition of frustum & look_at matrices, light intensity computations, .obj file format parser.
