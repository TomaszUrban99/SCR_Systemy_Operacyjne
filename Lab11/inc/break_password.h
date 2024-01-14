#ifndef BREAK_PASSWORD_H
#define BREAK_PASSWORD_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <openssl/evp.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "dictionary.h"
#include "user.h"

#define POSTFIXES 100
#define PREFIXES 100
#define ASCII_COUNT_BEGIN 48
#define ASCII_COUNT_END 57
#define ASCII_CHARACTER_BEGIN_UPPER 65
#define ASCII_CHARACTER_END_UPPER 90
#define ASCII_CHARACTER_BEGIN_LOWER 97
#define ASCII_CHARACTER_END_LOWER 122

/*!
    \brief breaked_password structure for storing information,
    whether password of given user has been breaked.
*/
struct breaked_password {

    /* Pointer to users structure defined in user.h */
    users *user;
    /* Breaked (not hashed) password */
    char breaked_password[PASSWORD_LENGTH];
    /* Store information whether password of given user has been breaked */
    int breaked_password_flag;

};

int break_password_wordlist (   struct dictionary_struct *dictionary, users *user, int user_array_size,
                                struct breaked_password *breaked_password_list);

void append_postfix ( char *password, int password_size, int postfix );

void append_prefix ( char *password, int password_size, int prefix );

void modify_dictionary_word ( char *modified_word, char *dictionary_word, int *prefix, int *postfix);

void modify_dictionary ( char *modified_word, char *dictionary_word, int *prefix, int *postfix);

void upper_first_dictionary_word ( char *password );

void upper_dictionary_word ( char *password, int password_size );

void test_postfixes( struct dictionary_struct *dictionary );

void print_breaked_passwords ( struct breaked_password* breaked_pass, int size_break );

/* -------------------- SECOND TERM - CHOCHLIK --------------------- */

void chochlik ( users* user_array, int number_of_users );

char generate_character ();

void pogromca_chochlika ( users* user_array, int index );

/* --------------------------------------------------------- */

#endif