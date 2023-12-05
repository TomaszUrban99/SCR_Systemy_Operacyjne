#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int main (int argc, char *argv[]){

    /* Test */

    int begin_argument;
    int end_argument;
    
    sscanf(argv[1], "%d", &begin_argument);
    sscanf(argv[2], "%d", &end_argument);

    printf("%u\n", prime_number_sum(begin_argument, end_argument));

    return 0;
}