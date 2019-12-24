 * @Library: RW_Lokers 
 * @author:  Mihai-Daniel Surcea
 * @date:    20.12.2019
 * @Subject: Operating Systems
 * @University of Bucharest, Faculty of Mathematics and Computer Science

This library is used to sincronize multiple readers and writers in the same buffer or memory zone (or any resources)

the compile command structure is: gcc -o [executableName] -pthread [fileUsingLibrary.c] RW_Lokers.c

This file contains a test which doesn't really uses any resources, but simulates it using sleep (the supposed time for that specific action)

The test should be used to test the functionality before using it in you code

The input file (.in) has the following structure:

	First line: n - number of readers + writers (if you have more they will be ignored)
	Next n lines format: rw t delay, where:
				 	   rw    - 0/1 (Reader/Writer) 
					   t     - execution time
					   delay - waiting time before the next request is included

