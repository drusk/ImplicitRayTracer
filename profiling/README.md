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