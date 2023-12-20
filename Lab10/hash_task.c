#include <openssl/evp.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>

#include "user.h"
#include "dictionary.h"
#include "break_password.h"

struct dictionary_struct dictionary;

struct breaked_password *break_pass;

int main ( int argc, char **argv ){

    /* -------------- READ USERS -------------------------------------------------------------------- */

    users user_array[20];
    int number_of_users = read_users(argv[1], user_array, 20);

    /*--------------- ALLOCATE MEMORY FOR ARRAY OF STRUCT BREAKED_PASSWORD --------------------------  */
    
    break_pass = (struct breaked_password*) malloc ( number_of_users * sizeof(struct breaked_password));

    /* Check whether memory has been allocated */
    if ( break_pass == NULL ){
        perror("Failed to allocate memory");
        return 2;
    }

    intitialize_dictionary(&dictionary);
    read_dictionary(argv[2],&dictionary);

    int break_index = break_password_wordlist(&dictionary, user_array, number_of_users, break_pass);

    print_breaked_passwords(break_pass, number_of_users);

    /*----------------- TIDY UP, FREE EXPLICITLY ALLOCATED MEMORY ------------------------------------ */
    free(break_pass);
    delete_structure(&dictionary);

    return 0;
}