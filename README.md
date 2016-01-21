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

struct queue q;

void thread_one()
{
    int i;
    char string[32];
    for(i=0; i<100; i++){
        sprintf(string, "%d", i);
        enqueue(&q, string, strlen(string));
    }
    pthread_exit(0);
}

void thread_two()
{
    int i;
    char string[32];
    for(i=0; i<100; i++){
        sprintf(string, "%d", 0-i);
        enqueue(&q, string, strlen(string));
    }
    pthread_exit(0);
}
int main()
{
    init_queue(&q);
    pthread_t one, two;
    pthread_create(&one, NULL, (void*)&thread_one, NULL);
    pthread_create(&two, NULL, (void*)&thread_two, NULL);
    pthread_join(one, NULL);
    pthread_join(two, NULL);
    char *buf = NULL;
    size_t size;
    int count=0, sum=0;
    while((buf = (char*)deque(&q, &size, 1)) != 0) {
        count++;
        fprintf(stderr, "size=%lu data= %s\n", size, buf);
        sum += atoi(buf);
        free(buf);
    }
    fprintf(stderr, "Number of Elements.(%d) Sum.(%d)\n", count, sum);
    return 0;
}
```
```console
...
...
...
size=2 data= 99
size=3 data= -95
size=3 data= -96
size=3 data= -97
size=3 data= -98
size=3 data= -99
Number of Elements.(200) Sum.(0)
```
### Development

Ongoing

License
----

MIT
