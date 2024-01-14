#ifndef USER_H
#define USER_H

#include "dictionary.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MAIL_LENGTH 50
#define USER_NAME 32

/*!
    \brief Users structure storing information about each user

    Stored information:
*/
typedef struct user {
    unsigned int user_id;
    char hashed_password[PASSWORD_LENGTH];
    char mail[MAIL_LENGTH];
    char user_name[USER_NAME];
} users;

/*!
    \brief Read users from file
*/
int read_users ( char *filename, users user_array[], int users_array_size);

/*!
    \brief Print users stored in array of structures 
*/
void print_users ( users *users_array, int users_array_size );

#endif