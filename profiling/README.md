Profiling
---------

Profiling is done using valgrind's profiler.  Usage is as follows

```
valgrind --tool=callgrind <executable>
```

This will take quite a while to run.  When it finishes, it will output a file called
callgrind.out.xxx where xxx is some number.  These profile outputs are copied to this 
directory.  They are renamed so that xxx is replaced by the first 7 characters of the 
SHA for the version of the code that was profiled.

The results can be visualized using kcachegrind:
```
kcachegrind callgrind.out.xxx
```

Notes
-----

callgrind.out.e5e3a1a: run with the following modifications 
(to reduce runtime):

* only green sphere and light in scene
* 25x25 image
* ray depth 1
* subdivision level 0
* implicit true
