#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <openssl/evp.h>
#include <string.h>

#define PASSWORD_LENGTH 33
#define DICTIONARY_SIZE 1000

/*!
	\brief
*/
struct dictionary_struct {
	char **word_list;
	int dictionary_size;
};

/*!
    \brief Inititalize dictionary_struct structure
*/
int intitialize_dictionary ( struct dictionary_struct *dictionary);

/*!
    \brief Read dictionary words
*/
int read_dictionary ( char *filename, struct dictionary_struct *dictionary);

/*!
    \brief List words in dictionary
*/
void print_dictionary ( struct dictionary_struct *dictionary );


void delete_structure ( struct dictionary_struct *dictionary );

/* Hash passwords */
void bytes2md5(const char *data, int len, char *md5buf);

#endif