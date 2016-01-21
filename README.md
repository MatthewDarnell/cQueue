# cQueue

cQueue is a simple, threadsafe queue data structure written in C.

  - simple
  - threadsafe
  - pthreads is the only dependency

### Version
0.0.1

### Building

simply include queue.h in your project and link with Queue.c and libpthread

```sh
$ clang main.c queue.c -lpthread
```


Sample Application:
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"
int main()
{
    struct queue q;
    init_queue(&q);
    enqueue(&q, "Hello, World!", 13);
    enqueue(&q, "Another String", 14);
    enqueue(&q, "Yet Another String Literal", 26);
    
    char *buf = NULL;
    size_t size = 0;
    while((buf = (char*)deque(&q, &size, 1)) != 0) {
        fprintf(stderr, "size=%lu data= %s\n", size, buf);
        free(buf);
    }
    return 0;
}
```
```console
size=13 data= Hello, World!
size=14 data= Another String
size=26 data= Yet Another String Literal

```
### Development

Ongoing

License
----

MIT
