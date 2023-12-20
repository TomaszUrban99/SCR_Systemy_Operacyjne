#include "break_password.h"

int break_password_wordlist (   struct dictionary_struct *dictionary, users *user, int user_array_size,
                                struct breaked_password *breaked_password_list){

    char hashed_password[PASSWORD_LENGTH];
    char modified_word[PASSWORD_LENGTH];
    
    int breaked_passwords = 0;
    int last_found = -1;

    for ( int j = 0; j < user_array_size; ++j ) {
        
        

        for ( int i = 0; i < dictionary->dictionary_size; ++i){
            
            for ( int k = -1; k < 100; ++k ){
                for ( int l = -1; l < 100; ++l){
                    
                    
                    if ( l == -1 && k == -1 ){
                        bytes2md5( dictionary->word_list[i], strlen(dictionary->word_list[i]), hashed_password);

                        if ( strcmp(user[j].hashed_password, hashed_password) == 0 ){

                            strcpy(breaked_password_list[j].breaked_password,dictionary->word_list[i]);
                            breaked_password_list[j].user = &user[j];
            
                            printf("%s%s%s\n", breaked_password_list[j].breaked_password, " ",  breaked_password_list[j].user->user_name);
                        
                            breaked_passwords++;
                            last_found = j;
                    
                        /*End looking for given user*/
                        k = 100;
                        l = 100;
                        i = dictionary->dictionary_size;

                        breaked_password_list[j].breaked_password_flag = 1;
                    }       
                    }
                    else {
                        
                        if ( l == -1 ){
                            modify_dictionary_word(modified_word,dictionary->word_list[i],NULL,&k);
                        } else if ( k == -1 ){
                            modify_dictionary_word(modified_word, dictionary->word_list[i], &l, NULL);
                        } else {
                            modify_dictionary_word(modified_word, dictionary->word_list[i], &l, &k);
                        }

                        bytes2md5( modified_word, strlen(modified_word), hashed_password);

                    if ( strcmp(user[j].hashed_password, hashed_password) == 0 ){

                        strcpy(breaked_password_list[j].breaked_password,modified_word);
                        breaked_password_list[j].user = &user[j];
            
                        printf("%s%s%s\n", breaked_password_list[j].breaked_password, " ",  breaked_password_list[j].user->user_name);
                        
                        breaked_passwords++;
                        last_found = j;
                    
                        /*End looking for given user*/
                        k = 100;
                        l = 100;
                        i = dictionary->dictionary_size;

                        breaked_password_list[j].breaked_password_flag = 1;
                    }           
                    }

                          
                }
            }       
        }   
        
        if ( last_found != j ){
                breaked_password_list[j].user = &user[j];
                breaked_password_list[j].breaked_password_flag = 0;
        }

      
    }

    return breaked_passwords;
}

void append_postfix ( char *password, int password_size, int postfix ){

    char postfix_array[3];
    sprintf(postfix_array, "%d", postfix);

    strcat(password, postfix_array);
}

void append_prefix ( char *password, int password_size, int prefix ){

    char prefix_array[PASSWORD_LENGTH];
    sprintf(prefix_array, "%d", prefix);
    strcat(prefix_array, password);
    strcpy(password,prefix_array);
}

void modify_dictionary_word ( char *modified_word, char *dictionary_word, int *prefix, int *postfix){

    strcpy(modified_word, dictionary_word);

    if ( prefix != NULL ){
        append_prefix( modified_word, strlen(modified_word), *prefix );
    }
    if ( postfix != NULL ){
        append_postfix( modified_word, strlen(modified_word), *postfix );
    }
}

void test_postfixes( struct dictionary_struct *dictionary ){

    int *prefix;
    int *postfix;

    /* Prefixes */
    for ( int i = 0; i < 20; ++i ){
        prefix = &i;
        postfix = &i;
        char modified_word[PASSWORD_LENGTH];
        modify_dictionary_word(modified_word, dictionary->word_list[0], prefix, postfix);
    }
}



void print_breaked_passwords ( struct breaked_password* breaked_pass, int size_break ){

    printf("%s%s%s\n", "USERNAME", "  ", "PASSWORD");

    for ( int i = 0; i < size_break; ++i ){

        if ( breaked_pass[i].breaked_password_flag )
            printf("%s%s%s\n", breaked_pass[i].user->user_name, "  ", breaked_pass[i].breaked_password );
    }
}
