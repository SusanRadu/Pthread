- Library: semaphore
- author: Radu Dilirici
- date: 03.01.2020
- Subject: Operating Systems
- University of Bucharest, Faculty of Mathematics and Computer Science

This library is used to synchronize multiple threads that share the same (finite) resources.

The compile structure is: gcc [your C file] sem.c -o [the name for the executable] -pthread

To test the functionality of the library you can compile and run the "bariera.c" file.
It contains the solution to the barier problem given at the OS laboratories, but solved with the semaphore from this library.
