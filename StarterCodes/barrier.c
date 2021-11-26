#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common_threads.h"

// If done correctly, each child should print their "before" message
// before either prints their "after" message. Test by adding sleep(1)
// calls in various locations.

// You likely need two semaphores to do this correctly, and some
// other integers to track things.

#define BARRIER_VALID   0xdbcafe
#define BARRIER_INITIALIZER(cnt) \
    {PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, \
    BARRIER_VALID, cnt, cnt, 0}

typedef struct __barrier_t {
    pthread_mutex_t     mutex;          /* Control access to barrier */
    pthread_cond_t      cv;             /* wait for barrier */
    int                 valid;          /* set when valid */
    int                 threshold;      /* number of threads required */
    int                 counter;        /* current number of threads */
    int                 cycle;          /* alternate wait cycles (0 or 1) */
} barrier_t;

// the single barrier we are using for this program
barrier_t b;

void barrier_init(barrier_t *b, int num_threads) {
        int status;

    b->threshold = b->counter = num_threads;
    b->cycle = 0;
    status = pthread_mutex_init (&b->mutex, NULL);
    if (status != 0)
        
    status = pthread_cond_init (&b->cv, NULL);
    if (status != 0) {
        pthread_mutex_destroy (&b->mutex);
        
    }
    b->valid = BARRIER_VALID;
    
}

void barrier(barrier_t *b) {
    // barrier code goes here
}

//
// XXX: don't change below here (just run it!)
//
typedef struct __tinfo_t {
    int thread_id;
} tinfo_t;

void *child(void *arg) {
    tinfo_t *t = (tinfo_t *) arg;
    printf("child %d: before\n", t->thread_id);
    barrier(&b);
    printf("child %d: after\n", t->thread_id);
    return NULL;
}


// run with a single argument indicating the number of 
// threads you wish to create (1 or more)
int main(int argc, char *argv[]) {
    assert(argc == 2);
    int num_threads = atoi(argv[1]);
    assert(num_threads > 0);

    pthread_t p[num_threads];
    tinfo_t t[num_threads];

    printf("parent: begin\n");
    barrier_init(&b, num_threads);
    
    int i;
    for (i = 0; i < num_threads; i++) {
	t[i].thread_id = i;
	Pthread_create(&p[i], NULL, child, &t[i]);
    }

    for (i = 0; i < num_threads; i++) 
	Pthread_join(p[i], NULL);

    printf("parent: end\n");
    return 0;
}

