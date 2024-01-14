#include "dictionary.h"

int intitialize_dictionary ( struct dictionary_struct *dictionary){

	dictionary->dictionary_size = DICTIONARY_SIZE;

    dictionary->word_list = (char **) malloc (DICTIONARY_SIZE * sizeof(char*));

	if ( dictionary->word_list == NULL){
		perror("Failed to allocate memory");
		return -1;
	}
    
    for ( int i = 0; i < DICTIONARY_SIZE; ++i ){
                    dictionary->word_list[i] = (char *) malloc(PASSWORD_LENGTH * sizeof(char));
    }


	return 0;

}

/*!
	\brief Read words to dictionary from list
*/
int read_dictionary ( char *filename, struct dictionary_struct *dictionary){

    /* Create new pointer and open file */
    FILE *ptr;
    ptr = fopen ( filename, "r" );
    int error_flag;

    for ( int i = 0; i < dictionary->dictionary_size; ++i ){
        error_flag = fscanf(ptr, "%s\n", dictionary->word_list[i]);
        if ( error_flag < 1){
			dictionary->dictionary_size = i;
			return i;
		}           
    }
    return dictionary->dictionary_size;
}

/*!
	\brief 
*/
void print_dictionary ( struct dictionary_struct *dictionary ){
	
	for ( int i = 0; i < dictionary->dictionary_size; ++i ){
        printf("%s\n", dictionary->word_list[i]);
    }
}

/*!
	\brief 
*/
void delete_structure ( struct dictionary_struct *dictionary ){

    for ( int i = 0; i < DICTIONARY_SIZE; ++i ){
        free(dictionary->word_list[i]);
    }

	free(dictionary->word_list);
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
