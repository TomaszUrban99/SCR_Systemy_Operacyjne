#include "break_password.h"

int break_password_wordlist (   struct dictionary_struct *dictionary, users *user, int user_array_size,
                                struct breaked_password *breaked_password_list){

    char hashed_password[PASSWORD_LENGTH];
    int breaked_passwords = 0;
    int last_found = -1;

    for ( int j = 0; j < user_array_size; ++j ) {

        for ( int i = 0; i < dictionary->dictionary_size; ++i){

        bytes2md5( dictionary->word_list[i], strlen(dictionary->word_list[i]), hashed_password);
        
        if ( strcmp(user[j].hashed_password, hashed_password) == 0 ){

            breaked_password_list[j].breaked_password = dictionary->word_list[i];
            breaked_password_list[j].user = &user[j];
            
            printf("%s%s%s\n", breaked_password_list[j].breaked_password, " ",  breaked_password_list[j].user->user_name);
            breaked_passwords++;
            last_found = j;
        }
        }

        if ( last_found != j ){
            breaked_password_list[j].user = &user[j];
            breaked_password_list[j].breaked_password = NULL;
        }

    }

    return breaked_passwords;
}


void print_breaked_passwords ( struct breaked_password* breaked_pass, int size_break ){

    printf("%s%s%s\n", "USERNAME", "  ", "PASSWORD");

    for ( int i = 0; i < 4; ++i ){

        if ( breaked_pass[i].breaked_password != NULL )
            printf("%s%s%s\n", breaked_pass[i].user->user_name, "  ", breaked_pass[i].breaked_password );
    }
}
