#include "break_password.h"

int break_password_wordlist ( struct dictionary_struct *dictionary, users *user){

    char hashed_password[PASSWORD_LENGTH];

    for ( int i = 0; i < dictionary->dictionary_size; ++i){

        bytes2md5( dictionary->word_list[i], strlen(dictionary->word_list[i]), hashed_password);

        
        if ( strcmp(user->hashed_password, hashed_password) == 0 ){
            return i;
        }
    }

    return -1;
}
