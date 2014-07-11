ImplicitRayTracer
=================

A simple ray tracer for implicit surfaces.

Implicit surfaces are defined by an 
[implicit function](http://en.wikipedia.org/wiki/Implicit_function).

Implicit surfaces can be rendered using either:

1. Ray tracing
2. Surface tiling/polygonization

In this project the 1st approach is taken.

Build and Run
-------------
Building uses [cmake](http://www.cmake.org/), 
tests use [googletest](https://code.google.com/p/googletest/) (included in the project
in the vendor directory).

There are no external dependencies.

* Run the application with ```run.sh```
* Run the tests with ```test.sh```

Acknowledgements
----------------
The original ray tracing code was heavily influenced by the lessons at
[scratchapixel](http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-1-writing-a-simple-raytracer/source-code/), though all code has been heavily refactored during
my process of understanding it.
