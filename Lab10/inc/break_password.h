#ifndef BREAK_PASSWORD_H
#define BREAK_PASSWORD_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <openssl/evp.h>
#include <string.h>

#include "dictionary.h"
#include "user.h"

int break_password_wordlist ( struct dictionary_struct *dictionary, users *user);

#endif