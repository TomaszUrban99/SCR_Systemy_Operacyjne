#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

#define THREADS_COUNT 5
#define COUNT 10

void* print_message(void* i){
    printf("%s%ld\n", "Hello OpSys. Written by thread ", *((long int*) pthread_self()));
    pthread_exit(NULL);
}

void* count(void* i){
    printf("%s%d\n", "Hello OpSys. Written by thread ", *(int *) i);
    int wynik = 0;
    for ( int j = 1; j < COUNT; ++j ){
        wynik = wynik + log(j);
    }
    printf("%s%d\n", "Wynik operacji: ", wynik);
    pthread_exit(NULL);
}

int main(){

    pthread_t threads_array[THREADS_COUNT];

    for ( int i = 0; i < THREADS_COUNT; ++i ){
        threads_array[i] = i;
        pthread_t new_thread_id;
        pthread_create(&new_thread_id, NULL, &count, &i);
        
    }

    for ( int i = 0; i < THREADS_COUNT; ++i ){
    pthread_join(threads_array[i], NULL);
    }
    return 0;
}



