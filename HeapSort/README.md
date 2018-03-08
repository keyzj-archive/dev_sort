ver1.0
Just a classic realization of Heap Sort (aka Pyramid Sort). Set DEBUG = 0, if you don't need it.
I've tried not to use any C++ features.
Obviously there's a lot to be done, but it's only first version.

ver1.1
Fixed small bugs, added upper limit for array size.
Finally added OpenMP.
Time example on my PC:
1 thread ~0.5s
8 threads ~0.07-0.09s
You're able to choose number of threads in sort.

ver2.0
Main: Fixed sorting algorithm, because older one has had a bug, which led to a wrong results.
Other: I've divided code into headers files with a little templates. Temporary deleted OpenMP support.
TODO: Add OpenMP support and retractor sorting algorithm to templates.

ver2.1
Main: Added templates support and minimum UI.
Other: Fixed n and m checks.
TODO: Add OpenMP support.
