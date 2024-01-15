#include <iostream>
#include <stdio.h>
#include <string>

#include "log.hh"
#include "record.hh"

int main(int argc, char **argv){

    /* Check number of input arguments */
    if ( argc < 1 ){
        perror("Wrong number of input arguments");
        exit(1);
    }

    log new_log;
    
    if ( new_log.read_log(argv[1]) == -1 ){
        perror("Failed to read log");
        exit(2);
    }

    std::cout << new_log;

    return 0;
}