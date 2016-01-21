#ifndef QUEUE_H
#define QUEUE_H
#include <pthread.h>
struct queueitem
{
    struct queueitem *prev, *next;
    void *data;
    size_t sz;
};
struct queue 
{
    struct queueitem *head, *tail;
    pthread_mutex_t mutex;
};

void init_queue(struct queue **q);
void enqueue(struct queue *q, void *mem, size_t nmemb);
void* deque(struct queue *q, size_t *sz, int pop);


#endif
