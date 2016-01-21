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


Sample Applications:

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"
int main()
{
    struct queue q;
    struct queue *ptrQ = &q;
    init_queue(&ptrQ);
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



Simple Multithreaded Application:
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"

struct queue *q;

void thread_one()
{
    int i;
    for(i=0; i<100; i++){
        enqueue(q, (void*)&i, sizeof(int));
    }
    pthread_exit(0);
}

void thread_two()
{
    int i, k;
    for(i=0; i<100; i++){
        k = 0-i;
        enqueue(q, (void*)&k, sizeof(int));
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
    while((buf = (char*)deque(q, &size, 1)) != 0) {
        count++;
        int *value = (int*)buf;
        fprintf(stderr, "size=%lu data= %d\n", size, *value);
        sum += *value;
        free(buf);
    }
    free(q);
    fprintf(stderr, "Number of Elements.(%d) Sum.(%d)\n", count, sum);
    return 0;
}
```
```console
...
...
...
size=4 data= 98
size=4 data= 99
size=4 data= -98
size=4 data= -99
Number of Elements.(200) Sum.(0)

```
### Development

Ongoing

License
----

MIT
