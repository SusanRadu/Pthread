- Library: semaphore
- author: Radu Dilirici
- date: 04.01.2020
- Subject: Operating Systems
- University of Bucharest, Faculty of Mathematics and Computer Science

This library is used to control access to a common resource by multiple threads.

The compile structure is: gcc [your C file] sem.c atomic.c -o [the name for the executable] -pthread

To test the functionality of the library you can compile and run the "bariera.c" file.
It contains the solution to the barier problem given at the OS laboratories, but solved with the semaphore from this library.
