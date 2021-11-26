#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

// If done correctly, each child should print their "before" message
// before either prints their "after" message. Test by adding sleep(1)
// calls in various locations.

sem_t s1, s2;

void *child_1(void *arg) {
    printf("child 1: before\n");
    sem_post(&s1);
    printf("child 1: after\n");
    sem_wait(&s2);
    return NULL;
}

void *child_2(void *arg) {
    printf("child 2: before\n");
    sem_post(&s1);
    printf("child 2: after\n");
    sem_wait(&s2);
    return NULL;
    sleep(1);
}

void *child_3(void *arg) {
    printf("child 3: before\n");
    sem_post(&s1);
    printf("child 3: after\n");
    sem_wait(&s2);
    return NULL;
    sleep(1);
}

void *child_4(void *arg) {
    printf("child 4: before\n");
    sem_post(&s1);
    printf("child 4: after\n");
    sem_wait(&s2);
    return NULL;
    sleep(1);
}

void *child_5(void *arg) {
    printf("child 5: before\n");
    sem_post(&s1);
    printf("child 5: after\n");
    sem_wait(&s2);
    return NULL;
    sleep(1);
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2, p3, p4, p5;
    printf("parent: begin\n");
    sem_open(&s1, 0, NULL);
    sem_open(&s2, 0, NULL);
    pthread_create(&p1, NULL, child_1, NULL);
    sleep(1);
    pthread_create(&p2, NULL, child_2, NULL);
    sleep(1);
    pthread_create(&p3, NULL, child_3, NULL);
    sleep(1);
    pthread_create(&p3, NULL, child_4, NULL);
    sleep(1);
    pthread_create(&p3, NULL, child_5, NULL);
    sleep(1);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    pthread_join(p5, NULL);
    printf("parent: end\n");
    return 0;
}

