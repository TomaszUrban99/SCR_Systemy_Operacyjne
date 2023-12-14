#include "user.h"

/* Read users */
int read_users ( char *filename, users user_array[], int users_array_size){

    /* Create file handle, open stream read-only */
    FILE *ptr;
    ptr = fopen ( filename, "r" );

    for ( int i = 0; i < users_array_size; ++i ){

        /* Read one line from input file */
        int error_flag = fscanf(ptr, "%d\t%s\t%s\t%s\n",   &user_array[i].user_id,  user_array[i].hashed_password,
                                        user_array[i].mail, user_array[i].user_name);

        /* fscanf returns number of read bytes, if number equals 0, break */
        if ( error_flag < 1){
            return i;
        }
    }

    return users_array_size;
}