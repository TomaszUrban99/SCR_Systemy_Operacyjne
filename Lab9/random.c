#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct father_and_sons {
    
    /* Pointer to 2D array */
    int **fields;

    /* Field dimensions */
    int dimension_X;
    int dimension_Y;

    /* Number of chance to each son */
    int chance;
    int sons;

    /* Number of sons still looking for fields */
    int sons_left;

    /* Array storing result of each son */
    int *result;

    /* Mutex and condition variable */
    pthread_mutex_t mutex_array;
    pthread_cond_t mutex_cond_var;
    
} structure_father;

/* Structure containing d*/
typedef struct coordinate_struct {
    int dimension_X;
    int dimension_Y;
} coordinates;

structure_father aufgabe;

void initialiesierung_aufgabe (   char *dimension_X[], char *dimension_Y[], 
                            char *number_of_sons[], char *number_of_chances[] ){

                /* ALLOCATING MEMORY ----------------------------------------------- */
                            sscanf(*dimension_X, "%d", &(aufgabe.dimension_X));
                            sscanf(*dimension_Y, "%d", &(aufgabe.dimension_Y));

                aufgabe.fields = (int **) malloc(aufgabe.dimension_X * sizeof(int* ));

                for ( int i = 0; i < aufgabe.dimension_X; ++i ){
                    aufgabe.fields[i] = (int *) malloc((aufgabe.dimension_Y)* sizeof(int));
                }

                /* INITIALIZE FIELDS WITH ZERO -------------------------------------- */
                for ( int i = 0; i < aufgabe.dimension_X; ++i ){
                    for ( int j = 0; j < aufgabe.dimension_Y; ++j ){
                        aufgabe.fields[i][j] = 0;
                    }
                }

                /* READ NUMBER OF SONS ---------------------------------------------- */
                            sscanf(*number_of_sons, "%d", &(aufgabe.sons));

                            /* Set number of sons still in game */
                            aufgabe.sons_left = aufgabe.sons;
                
                /* ALLOCATE MEMORY FOR ARRAY WITH RESULTS --------------------------- */
                    
                    aufgabe.result = (int *) malloc(aufgabe.sons * sizeof(int));
                    /* initialize array fields with zero */
                    for ( int i = 0; i < aufgabe.sons; ++i )
                        aufgabe.result[i] = 0;
                
                /* ------------------------------------------------------------------ */

                /* READ NUMBER OF CHANCES ------------------------------------------- */
                            sscanf(*number_of_chances, "%d", &(aufgabe.chance));

                /* INITIALIZE MUTEX AND CONDITION VARIABLE -------------------------- */
                    pthread_mutex_init(&aufgabe.mutex_array, NULL);
                    pthread_cond_init(&aufgabe.mutex_cond_var, NULL);
}

/* FREE ALLOCATED MEMORY ------------------------------------------------------------ */
void delete_aufgabe (){
    for ( int i = 0; i < aufgabe.dimension_X; ++i ){
        free(aufgabe.fields[i]);
    }

    free(aufgabe.fields);
}

/* GENERATE RANDOM COORDINATES ------------------------------------------------------ */
void generate_coordinates (          coordinates *coordinates_random, 
                                structure_father *father_struct ){
    /* Generate random number */                                
    coordinates_random->dimension_X = (int) (rand() % ( father_struct->dimension_X ));
    coordinates_random->dimension_Y = (int) (rand() % ( father_struct->dimension_Y ));
}

/* CHECK COORDINATES ---------------------------------------------------------------- */
int check_coordinates ( coordinates *coordinates_to_struct, int ***fields){
    
    if ( fields[coordinates_to_struct->dimension_X][coordinates_to_struct->dimension_Y] == 0 )
        return 0;
    else    
        return 1;
}

/* REJENT FUNCTION ----------------------------------------------------------------- */
void* rejent (void *rejent_arg){

    pthread_mutex_lock(&aufgabe.mutex_array);
    while (aufgabe.sons_left > 0){
        pthread_cond_wait(&aufgabe.mutex_cond_var, &aufgabe.mutex_array);
        aufgabe.sons_left--;
    }
    pthread_mutex_unlock(&aufgabe.mutex_array);
    
    printf("%s/n", "End!!!");
}

/* SON FUNCTION --------------------------------------------------------------------- */
void* son (void *son_arg){

    coordinates field_coordinates_to_check;
    int chances = aufgabe.chance;
    int field_status;

    printf("%s%d\n", "number of chances left: ", chances);

    while ( chances > 0 ){
        /* Generate random coordinates */
        generate_coordinates(&field_coordinates_to_check, &aufgabe);

        /* Block mutex and check state of field */
        pthread_mutex_lock(&aufgabe.mutex_array);
            
            field_status = check_coordinates(&field_coordinates_to_check, &aufgabe.fields);
            if ( field_status == 0 ){
                printf("%s", "Not!!!");
                /* Take over field */
                aufgabe.fields[field_coordinates_to_check.dimension_X][field_coordinates_to_check.dimension_Y] = 1;
                /* Increment result */
                aufgabe.result[field_coordinates_to_check.dimension_X]++;
            }
            else{
                printf("%s/", "Missed!!!");
                chances--;
            }
        /* Unblock mutex */
        pthread_mutex_unlock(&aufgabe.mutex_array);
    }

    /* If chances equal 0 send signal- no chances left */
    pthread_cond_signal(&aufgabe.mutex_cond_var);
}

int main (int argc, char *argv[]){

    coordinates coord;

    initialiesierung_aufgabe(&argv[1], &argv[2], &argv[3], &argv[4]);

    for ( int i = 0; i < 15; ++i ){
        generate_coordinates(&coord, &aufgabe);

        printf("%s%d%s%d\n", "Coordinate: ", coord.dimension_X, " ", coord.dimension_Y);
    }

    return 0;
}