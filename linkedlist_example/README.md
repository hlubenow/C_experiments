#### linkedlistexample 0.4

My attempt to implement a doubly linked list in C.

**Warning: This code is just experimental and may be buggy! Don't use it in production code!**

Such a list can be used to store different kind of elements (integers, strings and other lists of that kind at the moment), and it can be changed dynamically, that is, elements can be easily added or removed lateron. Quite similar to the "list" datatypes found in Python and Perl. Using these kind of lists may make C-programming a lot easier, but it may have a speed penalty.

In the code, I'm also using my C-emulation of classes here.

Meant to be used in Linux. Enter `make` to compile.

In real life, try using `#include <sys/queue.h>`, see the examples [here](https://github.com/TaborKelly/queue-example).

License: GNU GPL 3.
