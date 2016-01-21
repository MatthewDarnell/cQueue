#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"

void init_queue(struct queue *q)
{
    if(q == NULL){
        q = (struct queue*)malloc(sizeof(struct queue));
    }
    q->tail = q->head = NULL;
    pthread_mutex_init(&q->mutex, NULL);
}

void enqueue(struct queue *q, void *mem, size_t nmemb)
{
    pthread_mutex_lock(&q->mutex);

    if(q->tail == NULL){
        q->tail = (struct queueitem*)malloc(sizeof(struct queueitem));
        q->tail->prev = NULL;
        q->tail->next = NULL;
        q->head = q->tail;
        q->head->prev = NULL;
        q->head->next = NULL;
    }
    else{
        struct queueitem *newTail = (struct queueitem*)malloc(sizeof(struct queueitem));
        newTail->prev = q->tail;
        newTail->next = NULL;
	    q->tail->next = newTail;
        q->tail = newTail;
    }
    q->tail->data = (void*)malloc(nmemb);
    memcpy(q->tail->data, mem, nmemb);
    q->tail->sz = nmemb;
    pthread_mutex_unlock(&q->mutex);
}
void* deque(struct queue *q, size_t *sz, int pop)
{
    pthread_mutex_lock(&q->mutex);
    struct queueitem *oldHead = q->head;
    if(oldHead == NULL){
        pthread_mutex_unlock(&q->mutex);
        return 0;
    }
    void *buf = (void*)malloc(q->head->sz+1);
    memset(buf, 0, q->head->sz+1);
    memcpy(buf, q->head->data, q->head->sz);
    *sz = q->head->sz;
    if(pop != 0){
        if(q->head->next != NULL){
            q->head = q->head->next;
            q->head->prev = NULL;
        }
        else{
            q->head = q->tail = NULL;
        }
        free(oldHead->data);
        free(oldHead);
    }
    pthread_mutex_unlock(&q->mutex);
    return buf;
}

