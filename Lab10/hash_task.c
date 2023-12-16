#include <openssl/evp.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>

#include "user.h"
#include "dictionary.h"
#include "break_password.h"

struct dictionary_struct dictionary;

int main ( int argc, char **argv ){
    
    users user_array[20];
    int number_of_users = read_users(argv[1], user_array, 20);

    intitialize_dictionary(&dictionary);
    read_dictionary(argv[2],&dictionary);

    int break_index = break_password_wordlist(&dictionary, &user_array[0]);
    if ( break_index != -1 ){
        printf("%s%s\n" "Found password: ", dictionary.word_list[break_index]);
    }
    else
        printf("%s\n", "Password not found" );

    delete_structure(&dictionary);

    return 0;
}