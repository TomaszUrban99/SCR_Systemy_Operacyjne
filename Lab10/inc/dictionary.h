#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <openssl/evp.h>
#include <string.h>

#define DICTIONARY_SIZE 1000

/*!
    \brief Read dictionary words
*/
int read_dictionary ( char *filename, char **passwords, int dictionary_size);

/* Hash passwords */
void bytes2md5(const char *data, int len, char *md5buf);


#endif