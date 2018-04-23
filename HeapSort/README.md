About commit versions
Bassically version with structure "number.number" is complete version, which is ready to build.
But version with extra part ("*.number") is [WIP] version, this version MUST NOT be used (often it can't even compile).
So, for example, in order to build and use this program choose version 2.3, but not 2.3.x.

Versions log
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

ver2.2
Main: added tasks.h and tasks.cpp + ut dir.
Other: small fixed.
TODO: Add OpenMP support + add more ut.

ver2.3
Main: changed directory name to "heap-sort" & project was unified to right composition.
Other: UT is temporary commented.
TODO: rewrite main algorithms, sort & UT.

ver2.4
Main: added biotype, biopart unification types, now sort() recieve biopart and sort it separately from others parts.
Temporary: sorting in 1 thread, using just an vector<biotype> instead of vector<biotype_ptr> ==> biopart uses biotype_ptr for begin, end (not biotype_ptr *).
TODO: add OMP support for sort(), take care of collisions, start to use vector<biotype_ptr> (and all that follows from this).

ver3.0
Main: everything is working properly, added dealWithCollisions, but just resorting bio_data works much more faster. 
      Deleted manually choice of threads, Biopart know own size now & more smaller changes.
TODO: clean up code a little & maybe add UT.

ver3.1 [final]
Main: cleaned up code.

