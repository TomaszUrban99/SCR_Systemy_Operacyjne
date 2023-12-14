#include "dictionary.h"

int read_dictionary ( char *filename, char **passwords, int dictionary_size){

    /* Create new pointer and open file */
    FILE *ptr;
    ptr = fopen ( filename, "r" );
    int error_flag;

    for ( int i = 0; i < dictionary_size; ++i ){
        error_flag = fscanf(ptr, "%s\n", passwords[i]);
        if ( error_flag < 1)
            return i;
    }

    return dictionary_size;
}

/* Hash passwords */
void bytes2md5(const char *data, int len, char *md5buf) {
	EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
	const EVP_MD *md = EVP_md5();
	unsigned char md_value[EVP_MAX_MD_SIZE];
	unsigned int md_len, i;
	EVP_DigestInit_ex(mdctx, md, NULL);
	EVP_DigestUpdate(mdctx, data, len);
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);
	EVP_MD_CTX_free(mdctx);
	for (i = 0; i < md_len; i++) {
		snprintf(&(md5buf[i * 2]), 16 * 2, "%02x", md_value[i]);
	}
}
