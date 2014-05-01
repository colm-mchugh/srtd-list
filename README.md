srtd-list
=========

The code in list.h and list.cpp implements a doubly linked list.
There are two functions in the API (list.h) which will maintain or produce a sorted list:
  1. `addInSortedOrder` - Adds an element to a list in sorted order using the given comparison function
  2. `mergesort` - Sorts a list using the given comparison function

The demo program measures how long it takes to populate lists of varying sizes, using the above two 
functions to produce a sorted list. 

Implementation Notes
--------------------
To compile and run the demo program:

```
$ make
$ ./srtd_list_demo
```

Written in C using some C++ features. Built and tested on ubuntu 12.04. (GNU g++ 4.8.1, GNU Make 3.81)
  
Example output
--------------

For lists under 1024 words, there is no appreciable difference between the two methods of producing a sorted list, 
but for larger lists the method of appending all the words followed by merge sorting the list becomes increasingly
attractive, showing the difference in the underlying algorithms (n*log(n) for mergesort, n-squared for adding in 
sorted order, where n is the number of nodes in the list)

```
$ ./srtd_list_demo
Append followed by mergesort 16 nodes: 25 usecs (0 seconds)
Adding in sorted order 16 nodes: 14 usecs (0 seconds)

Append followed by mergesort 64 nodes: 45 usecs (0 seconds)
Adding in sorted order 64 nodes: 31 usecs (0 seconds)

Append followed by mergesort 256 nodes: 120 usecs (0 seconds)
Adding in sorted order 256 nodes: 340 usecs (0 seconds)

Append followed by mergesort 1024 nodes: 505 usecs (0 seconds)
Adding in sorted order 1024 nodes: 5194 usecs (0 seconds)

Append followed by mergesort 4096 nodes: 2277 usecs (0 seconds)
Adding in sorted order 4096 nodes: 48864 usecs (0 seconds)

Append followed by mergesort 8192 nodes: 2499 usecs (0 seconds)
Adding in sorted order 8192 nodes: 180279 usecs (0 seconds)

Append followed by mergesort 16384 nodes: 4990 usecs (0 seconds)
Adding in sorted order 16384 nodes: 18446744073709398018 usecs (1 seconds)

Append followed by mergesort 32768 nodes: 11564 usecs (0 seconds)
Adding in sorted order 32768 nodes: 18446744073709233008 usecs (4 seconds)

Append followed by mergesort 65536 nodes: 28556 usecs (0 seconds)
Adding in sorted order 65536 nodes: 18446744073709470991 usecs (21 seconds)

```

Environment notes:

```
$ uname -mrs
Linux 3.8.0-37-generic x86_64

$ lsb_release -a
No LSB modules are available.
Distributor ID: Ubuntu
Description:    Ubuntu 12.04.4 LTS
Release:        12.04
Codename:       precise
```
