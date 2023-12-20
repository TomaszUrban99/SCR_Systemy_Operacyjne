#ifndef BREAK_PASSWORD_H
#define BREAK_PASSWORD_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <openssl/evp.h>
#include <string.h>

#include "dictionary.h"
#include "user.h"

struct breaked_password {
    
    users *user;
    char *breaked_password;

};

int break_password_wordlist (   struct dictionary_struct *dictionary, users *user, int user_array_size,
                                struct breaked_password *breaked_password_list);

void append_postfix ( char *password, int password_size, int postfix );

void append_prefix ( char *password, int password_size, int prefix );

void modify_dictionary_word ( char *modified_word, char *dictionary_word, int *prefix, int *postfix);

void test_postfixes( struct dictionary_struct *dictionary );

void print_breaked_passwords ( struct breaked_password* breaked_pass, int size_break );

#endif