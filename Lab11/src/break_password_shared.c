#include "break_password_shared.h"

/*!
    \brief
*/
void* producer ( void* break_password_shared ){

    printf("%s\n", "Created....");

    /* Cast break_password_shared pointer to struct break_password_shared */
    struct break_password_shared *new_break = (struct break_password_shared *) break_password_shared; 

    /* Initialize variable to store information about number of words in dictionary */
    int dictionary_size = new_break->dictionary.dictionary_size;
    printf("%s%d\n", "Dictionary size: ", dictionary_size);

    /* Get current user */
    pthread_mutex_lock(&new_break->current_user_mutex);
    int current_user = new_break->current_user;
    new_break->current_user++;
    pthread_mutex_unlock(&new_break->current_user_mutex); 

    while ( current_user < new_break->number_of_users){

        /* Array to store hashed passwords */
        char hashed_password[PASSWORD_LENGTH];     
        /* Array to store modified word */
        char modified_word[PASSWORD_LENGTH];

        
        /* Iterate through dictionary */
        for ( int i = 0; i < dictionary_size; ++i){
            
             /* Copy dictionary word */
            char modified_word_2[PASSWORD_LENGTH];      
            strcpy(modified_word_2, new_break->dictionary.word_list[i]);
            
            for ( int up_low = 0; up_low < 3; up_low++){
      
                if ( up_low == 1)
                    upper_first_dictionary_word(modified_word_2);
                if ( up_low == 2)
                    upper_dictionary_word(modified_word_2, strlen(modified_word_2));

                for ( int k = -1; k < POSTFIXES; ++k ){

                    for ( int l = -1; l < PREFIXES; ++l){          
                        
               
                    /* Different possibilities */
                    if ( l == -1 && k == -1 ){
                            modify_dictionary(modified_word,modified_word_2,NULL,NULL);
                    } else if ( l == -1 ){
                            modify_dictionary(modified_word,modified_word_2,NULL,&k);
                    } else if ( k == -1 ){
                            modify_dictionary(modified_word, modified_word_2, &l, NULL);
                    } else {
                            modify_dictionary(modified_word, modified_word_2, &l, &k);
                    }

                    /* ---------------------- HASH MODIFIED WORD ------------------------------ */
                    bytes2md5( modified_word, strlen(modified_word), hashed_password);

                    if ( strcmp(new_break->users_array[current_user].hashed_password, hashed_password) == 0 ){

                        strcpy(new_break->breaked_password_array[current_user].breaked_password, modified_word);

                        /*End looking for given user*/
                        k = POSTFIXES;
                        l = PREFIXES;
                        up_low = 3;
                        i = dictionary_size;

                        new_break->breaked_password_array[current_user].breaked_password_flag = 1;

                          printf("%s%d\n", "Current user: ", current_user);

                        printf("%s%s%s%s\n", "User: ", new_break->users_array[current_user].user_name, " Password: ", 
                            new_break->breaked_password_array[current_user].breaked_password );
                    }                                    
                    }
                }       
            }
        }

        /* Get current user */
        pthread_mutex_lock(&new_break->current_user_mutex);
        current_user = new_break->current_user;
        new_break->current_user = new_break->current_user+1;
        pthread_mutex_unlock(&new_break->current_user_mutex); 
    }
}

/*!
    \brief 
*/
void* consumer ( void* arg ){

}

int break_password_user (){

}