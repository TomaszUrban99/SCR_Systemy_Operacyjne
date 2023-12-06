#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>

/* Structure */
typedef struct prime_numbers_sums_t {
    unsigned int N;
    unsigned int M;
    unsigned int K;
    unsigned int sprawdz;
    unsigned int znalezione;
    int found_flag;
    long suma;

} prime_numbers_sums;

prime_numbers_sums prime_struct;

/* Initialize prime_number_sums structure */
void set_prime_number_structure (prime_numbers_sums *prime_struct,
                                        char *argument_1[], char *argument_2[], char *argument_3[] )
{ 
    sscanf(*argument_1, "%d", &(prime_struct->N));
    sscanf(*argument_2, "%d", &(prime_struct->M));
    sscanf(*argument_3, "%d", &(prime_struct->K));

    prime_struct->sprawdz = prime_struct->M;
    prime_struct->znalezione = 0;
    prime_struct->suma = 0;
    prime_struct->found_flag = 0;
}

/* Check whether given number is a prime number */
unsigned int is_prime_number(unsigned int number_to_check){

    if ( number_to_check < 2)
        return 0;

    for ( int i = 2; i < number_to_check; i++ ){
        if ( (number_to_check % i) == 0 )
            return 0;
    }

    return number_to_check;
}

/* Count number of */
unsigned int prime_number_sum ( int begin, int end ){

    /* Sum of prime numbers */
    unsigned int sum = 0;
    unsigned int a = 0;

    /* Prime numbers counter */
    int i = 0;
    /* To iterate thorug numbers */
    int j = 0;

    while ( i < end ){
        /* If begin+j is a prime number, then add it to sum */
        if ( (a=is_prime_number(begin + j)) > 0){
            sum = sum + a;
            i++;
        }
        j++;
    }

    return sum;
}

void *count_prime_number_sum_multi (){

    while (!prime_struct.found_flag){

    /* --------------------------------------------------- */
    /*           Read number to check                      */
    /* --------------------------------------------------- */

        /* Number to check */
        int number_to_check = prime_struct.sprawdz;
        /* Next number should be checked */
        prime_struct.sprawdz++;

    /* ---------------------------------------------------- */
    /* Variable to store sum                                */
    /* ---------------------------------------------------- */
    int a; 

    if ( (a = is_prime_number(number_to_check)) > 0){
         
            /* Add to sum */

            /* Check whether enough prime numbers have been found */
            if (prime_struct.znalezione < prime_struct.N){
                prime_struct.suma +=  a;
                /* Increment number of found prime numbers */
                prime_struct.znalezione++;
                
                if ( prime_struct.N == prime_struct.znalezione ){
                prime_struct.found_flag = 1;
            }
            }
    }    
    }


}

int main (int argc, char *argv[]){

    struct timespec time_struct_before;
    struct timespec time_struct_after;

    clock_gettime(CLOCK_REALTIME, &time_struct_before);

    /* Check number of input arguments */
    if ( argc < 3){
        perror("Wrong input arguments");
        return -1;
    }

    /* Set prime_number_structure */
    set_prime_number_structure(&prime_struct, &argv[1], &argv[2], &argv[3]);

    /* Create threads */
    int number_of_threads = prime_struct.K;
    /* Allocate memory for array */
    pthread_t *new_threads_id = (pthread_t *) malloc(sizeof(pthread_t) * number_of_threads);
    
    /* Loop and create threads */
    for ( int i = 0; i < number_of_threads; ++i ){
        
        new_threads_id[i] = i;
        pthread_create(&new_threads_id[i], NULL, &count_prime_number_sum_multi, NULL );
        /*pthread_join(new_thread_id, NULL);*/
    }

    for ( int i = 0; i < number_of_threads; ++i ){
        pthread_join(new_threads_id[i],NULL);
    }

    clock_gettime(CLOCK_REALTIME, &time_struct_after);

    printf("%s%ld\n", "Sum of prime numbers: ", prime_struct.suma );
    printf("%s%ld\n", "Time: ", time_struct_after.tv_sec - time_struct_before.tv_sec );

    /* Free memory */
    free(new_threads_id);

    return 0;
}