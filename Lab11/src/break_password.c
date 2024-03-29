#include "break_password.h"

int break_password_wordlist (   struct dictionary_struct *dictionary, users *user, int user_array_size,
                                struct breaked_password *breaked_password_list){

    char hashed_password[PASSWORD_LENGTH];
    
    
    int breaked_passwords = 0;
    int last_found = -1;

    for ( int j = 0; j < user_array_size; ++j ) {
        
        for ( int i = 0; i < dictionary->dictionary_size; ++i){
            
            char modified_word[PASSWORD_LENGTH];
            
            for ( int up_low = 0; up_low < 3; up_low++){
                
                /* Copy dictionary word */
                char modified_word_2[PASSWORD_LENGTH];  
                strcpy(modified_word_2, dictionary->word_list[i]);
      
                if ( up_low == 1)
                    upper_first_dictionary_word(modified_word_2);
                if ( up_low == 2)
                    upper_dictionary_word(modified_word_2, strlen(modified_word_2));

                for ( int k = -1; k < POSTFIXES; ++k ){

                    for ( int l = -1; l < PREFIXES; ++l){

                    /* Different possibilities */
                    if ( l == -1 && k == -1 ){
                            modify_dictionary_word(modified_word,modified_word_2,NULL,NULL);
                    } else if ( l == -1 ){
                            modify_dictionary_word(modified_word,modified_word_2,NULL,&k);
                    } else if ( k == -1 ){
                            modify_dictionary_word(modified_word, modified_word_2, &l, NULL);
                    } else {
                            modify_dictionary_word(modified_word, modified_word_2, &l, &k);
                    }

                    /* ---------------------- HASH MODIFIED WORD ------------------------------ */
                    bytes2md5( modified_word, strlen(modified_word), hashed_password);

                    if ( strcmp(user[j].hashed_password, hashed_password) == 0 ){

                        strcpy(breaked_password_list[j].breaked_password,modified_word);
                        breaked_password_list[j].user = &user[j];
                        
                        breaked_passwords++;
                        last_found = j;
                    
                        /*End looking for given user*/
                        k = POSTFIXES;
                        l = PREFIXES;
                        up_low = 3;
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

void upper_first_dictionary_word ( char *password ){
    password[0] = toupper(password[0]);
}

void upper_dictionary_word ( char *password, int password_size ){

for (int i = 0; i < password_size; ++i ){
    password[i] = toupper(password[i]);
}
}

void append_postfix ( char *password, int password_size, int postfix ){

    char postfix_array[3];
    sprintf(postfix_array, "%d", postfix);
    strcat(password, postfix_array);
}

void append_prefix ( char *password, int password_size, int prefix ){

    char prefix_array[PASSWORD_LENGTH];
    sprintf(prefix_array, "%d", prefix);

    int size_of_prefix = strlen(prefix_array);

    strcat(prefix_array, password);
    strcpy(password, prefix_array);
}

void modify_dictionary_word ( char *modified_word, char *dictionary_word, int *prefix, int *postfix){

    if ( prefix != NULL ){
        append_prefix( modified_word, strlen(modified_word), *prefix );
    }
    if ( postfix != NULL ){
        append_postfix( modified_word, strlen(modified_word), *postfix );
    }
}

void modify_dictionary ( char *modified_word, char *dictionary_word, int *prefix, int *postfix){

    modified_word[0] = '\0';
    
    if ( prefix != NULL ){
        sprintf(modified_word, "%d", *prefix);
    }

    strcat(modified_word,dictionary_word);

    if ( postfix != NULL ){
        char postfix_array[3];
        sprintf(postfix_array,"%d", *postfix);
        strcat(modified_word, postfix_array);
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

void generate_random_password ( char *hashed_password ) {


    char password[PASSWORD_LENGTH] = {0};

    /* Random size of password in range from 1 to 32 */
    int password_size = rand () % PASSWORD_LENGTH;
    int letter_or_count;

    for ( int i = 0; i < password_size; ++i ){
        
        /* Decide whether letter or count */
        letter_or_count = rand () % 3;

        /* If letter, generate letter */
        if ( letter_or_count == 1 ){
            password[i] = rand () % ( ASCII_CHARACTER_END_UPPER + 1 - ASCII_CHARACTER_BEGIN_UPPER ) + ASCII_CHARACTER_BEGIN_UPPER;
        }
        /* Else generate count*/
        else if ( letter_or_count == 2) {
            password[i] = rand () % ( ASCII_COUNT_END + 1 - ASCII_COUNT_BEGIN ) + ASCII_COUNT_BEGIN;
        }
        else {
            password[i] = rand () % ( ASCII_CHARACTER_END_LOWER + 1 - ASCII_CHARACTER_BEGIN_LOWER ) + ASCII_CHARACTER_BEGIN_LOWER;
        }
    }

    printf("%s%s\n", "Generated password: ", password);
    bytes2md5(password, strlen(password), hashed_password);
}

void chochlik ( users *user_array, int number_of_users){

    /* Generate random index */
    srand(time(NULL));
    int index = rand () % number_of_users;

    generate_random_password(user_array[index].hashed_password);
}

char generate_character () {

    int letter_or_count;
   
        /* Decide whether letter or count */
        letter_or_count = rand () % 3;

        /* If letter, generate letter */
        if ( letter_or_count == 1 ){
            return (rand () % ( ASCII_CHARACTER_END_UPPER + 1 - ASCII_CHARACTER_BEGIN_UPPER ) + ASCII_CHARACTER_BEGIN_UPPER);
        }
        /* Else generate count*/
        else if ( letter_or_count == 2) {
            return (rand () % ( ASCII_COUNT_END + 1 - ASCII_COUNT_BEGIN ) + ASCII_COUNT_BEGIN);
        }
        else {
            return (rand () % ( ASCII_CHARACTER_END_LOWER + 1 - ASCII_CHARACTER_BEGIN_LOWER ) + ASCII_CHARACTER_BEGIN_LOWER);
        }
}



void pogromca_chochlika ( users* user_array, int index ){
    
    int size_of_password = 1;

    char hashed_password[PASSWORD_LENGTH];

    for ( int i = 1; i < PASSWORD_LENGTH; ++i ){
        
        char password[PASSWORD_LENGTH] = {0};
        


        bytes2md5(password, i, hashed_password);
        
        if ( strcmp ( hashed_password, user_array[index].hashed_password ) == 0){
            printf("%s%s\n", "Found password: ", password);
        }
    }


}
