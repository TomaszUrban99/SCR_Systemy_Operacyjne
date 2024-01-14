#include <openssl/evp.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>

#include "user.h"
#include "dictionary.h"
#include "break_password.h"
#include "break_password_shared.h"

/* Structure for enabling cooperation between threads */
struct break_password_shared break_passwords_sh_mem;

int main ( int argc, char **argv ){

    /* Initialize random number generator */
    srand(time(NULL));

    /* -------------- READ USERS -------------------------------------------------------------------- */

    int number_of_users = read_users(argv[1], break_passwords_sh_mem.users_array, NUMBER_OF_USERS);
    break_passwords_sh_mem.number_of_users = number_of_users;
    break_passwords_sh_mem.current_user = 0;

    print_users(break_passwords_sh_mem.users_array, number_of_users);

    /* ------------- INITIALIZE MUTEX ---------------------------------------------------------------- */
    pthread_mutex_init(&break_passwords_sh_mem.current_user_mutex,NULL);

    /*--------------- ALLOCATE MEMORY FOR ARRAY OF STRUCT BREAKED_PASSWORD --------------------------  */
    
    break_passwords_sh_mem.breaked_password_array = (struct breaked_password*) 
        malloc ( break_passwords_sh_mem.number_of_users * sizeof(struct breaked_password));

    /* Check whether memory has been allocated */
    
    if ( break_passwords_sh_mem.breaked_password_array == NULL ){
        perror("Failed to allocate memory");
        return 2;
    }

    /* ----------------------------------------------------------------------------------------------- */

    /* --------------------------- INITIALIZE AND READ DICTIONARY ------------------------------------ */
    
    intitialize_dictionary(&break_passwords_sh_mem.dictionary);
    break_passwords_sh_mem.dictionary.dictionary_size = read_dictionary(argv[2],&break_passwords_sh_mem.dictionary);
    printf("%s\n", "Read dictionary");
    
    /* ----------------------------------------------------------------------------------------------- */

    /* ------------------------------------------------------------------------------------------------ */

    pthread_t *new_threads_id = (pthread_t *) malloc(sizeof(pthread_t) * THREADS_NUMBER);
    pthread_create(&new_threads_id[0], NULL, &consumer, NULL );
    
    /* Loop and create threads */
    for ( int i = 1; i < THREADS_NUMBER; ++i ){
        
        new_threads_id[i] = i;
        pthread_create(&new_threads_id[i], NULL, &producer, &break_passwords_sh_mem );
        /*pthread_join(new_thread_id, NULL);*/
    }

    for ( int i = 0; i < THREADS_NUMBER; ++i ){
        pthread_join(new_threads_id[i],NULL);
    }

    /* ---------------- TIDY UP, FREE EXPLICITLY ALLOCATED MEMORY ------------------------------------- */
    
    free(break_passwords_sh_mem.breaked_password_array);
    free(new_threads_id);
    delete_structure(&break_passwords_sh_mem.dictionary);

    return 0;
}