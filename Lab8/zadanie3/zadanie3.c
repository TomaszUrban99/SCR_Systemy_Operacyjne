#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int is_prime_number(int number_to_check){

    if ( number_to_check < 2)
        return -1;

    int begin = 2;

    for ( int i = 2; i < number_to_check; i++ )
    {
        if ( number_to_check % i == 0 )
            return -1;
    }

    return number_to_check;
}

int main (int argc, char *argv[]){

    /* Test */

    int input_argument;
    sscanf(argv[1], "%d", &input_argument);
    printf("%d\n", is_prime_number(input_argument));

    return 0;
}