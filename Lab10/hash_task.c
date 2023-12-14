#include <openssl/evp.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>

#include "user.h"
#include "dictionary.h"
#include "dictionary.h"

int main ( int argc, char **argv ){
    
    users user_array[20];
    int number_of_users = read_users(argv[1], user_array, 20);

    for ( int i = 0; i < number_of_users; ++i )
    {
        printf("%d \t %s \t %s \t %s\n", user_array[i].user_id, user_array[i].hashed_password, 
            user_array[i].mail, user_array[i].user_name );
    }

    char **password;

    password = (char **) malloc (DICTIONARY_SIZE * sizeof(char*));
    
    for ( int i = 0; i < DICTIONARY_SIZE; ++i ){
                    password[i] = (char *) malloc(PASSWORD_LENGTH * sizeof(char));
                }

            
    int number_of_words = read_dictionary(argv[2], password, DICTIONARY_SIZE);

    for ( int i = 0; i < number_of_words; ++i ){
        printf("%s\n", password[i]);
    }

    for ( int i = 0; i < DICTIONARY_SIZE; ++i ){
        free(password[i]);
    }

    free(password);

    return 0;
}