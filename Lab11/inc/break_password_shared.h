#ifndef BREAK_PASSWORD_SHARED_H
#define BREAK_PASSWORD_SHARED_H

#include <stdlib.h>

#include "break_password.h"

#define THREADS_NUMBER 16
#define NUMBER_OF_USERS 40

struct break_password_shared {

    /* Number of users to break passwords */
    int number_of_users;
    /* Index of current user */
    int current_user;
    /* Array of users with passwords */
    struct breaked_password *breaked_password_array;
    /* Users array */
    users users_array[NUMBER_OF_USERS];
    /* Pointer to dictionary struct */
    struct dictionary_struct dictionary;
    pthread_mutex_t current_user_mutex;
};

int break_password_user ();

void* producer ( void* arg );

void* consumer ( void* arg );

#endif