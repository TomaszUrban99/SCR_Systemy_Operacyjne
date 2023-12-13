#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bits/pthreadtypes.h>

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

    pthread_mutex_t mutex_chances_left;
    pthread_cond_t mutex_cond_var;

    /* Barrier */
    pthread_barrier_t barrier;
    
} structure_father;

/* Structure containing d*/
typedef struct coordinate_struct {
    int dimension_X;
    int dimension_Y;
} coordinates;

structure_father aufgabe;

pthread_t *threads;

void initialiesierung_aufgabe (   structure_father *aufgabe_data, char *dimension_X[], char *dimension_Y[], 
                            char *number_of_sons[], char *number_of_chances[] ){

                /* ALLOCATING MEMORY ----------------------------------------------- */
                            sscanf(*dimension_X, "%d", &(aufgabe_data->dimension_X));
                            sscanf(*dimension_Y, "%d", &(aufgabe_data->dimension_Y));

                aufgabe_data->fields = (int **) malloc(aufgabe_data->dimension_X * sizeof(int* ));

                for ( int i = 0; i < aufgabe.dimension_X; ++i ){
                    aufgabe_data->fields[i] = (int *) malloc((aufgabe.dimension_Y)* sizeof(int));
                }

                /* INITIALIZE FIELDS WITH ZERO -------------------------------------- */
                for ( int i = 0; i < aufgabe_data->dimension_X; ++i ){
                    for ( int j = 0; j < aufgabe_data->dimension_Y; ++j ){
                        aufgabe_data->fields[i][j] = 0;
                    }
                }

                /* READ NUMBER OF SONS ---------------------------------------------- */
                            sscanf(*number_of_sons, "%d", &(aufgabe_data->sons));

                            /* Set number of sons still in game */
                            aufgabe_data->sons_left = aufgabe_data->sons;
                
                /* ALLOCATE MEMORY FOR ARRAY WITH RESULTS --------------------------- */
                    
                    aufgabe_data->result = (int *) malloc(aufgabe_data->sons * sizeof(int));
                    /* initialize array fields with zero */
                    for ( int i = 0; i < aufgabe_data->sons; ++i )
                        aufgabe_data->result[i] = 0;
                
                /* ------------------------------------------------------------------ */

                /* READ NUMBER OF CHANCES ------------------------------------------- */
                            sscanf(*number_of_chances, "%d", &(aufgabe_data->chance));

                /* INITIALIZE MUTEX AND CONDITION VARIABLE -------------------------- */
                    pthread_mutex_init(&aufgabe_data->mutex_array, NULL);
                    pthread_mutex_init(&aufgabe_data->mutex_chances_left, NULL);
                    pthread_cond_init(&aufgabe_data->mutex_cond_var, NULL);

                /* INITIALIZE BARRIER */
                    pthread_barrier_init(&aufgabe_data->barrier, NULL, aufgabe_data->sons);
}

/* FREE ALLOCATED MEMORY ------------------------------------------------------------ */
void delete_aufgabe (){
    for ( int i = 0; i < aufgabe.dimension_X; ++i ){
        free(aufgabe.fields[i]);
    }

    free(aufgabe.fields);
}

void print_field( structure_father *aufgabe_data){
    for ( int i = 0; i < aufgabe_data->dimension_X; ++i){
        for ( int j = 0; j < aufgabe_data->dimension_Y; ++j){
            printf("%d%s", aufgabe_data->fields[i][j], " ");
        }

        printf("\n");
    }
}

void print_results ( structure_father *aufgabe_data){
    printf ("%s\n", "Son number    |   Result ");
    for ( int i = 0; i < aufgabe_data->sons; ++i )
    {
        printf("%d%s%d\n", i+1, "             |   ", aufgabe_data->result[i]);
    }
}

/* GENERATE RANDOM COORDINATES ------------------------------------------------------ */
void generate_coordinates (          coordinates *coordinates_random, 
                                int dimensionX, int dimensionY ){
    /* Generate random number */                                
    coordinates_random->dimension_X = (int) (rand() % ( dimensionX ));
    coordinates_random->dimension_Y = (int) (rand() % ( dimensionY ));
}

/* CHECK COORDINATES ---------------------------------------------------------------- */
int check_coordinates ( coordinates *coordinates_to_struct, int **fields){

    if ( fields[coordinates_to_struct->dimension_X][coordinates_to_struct->dimension_Y] == 0 ){
        return 0;
    }
    else    
        return 1;
}

/* REJENT FUNCTION ----------------------------------------------------------------- */
void* rejent (void *rejent_arg){

    pthread_mutex_lock(&aufgabe.mutex_chances_left);
    
    while (aufgabe.sons_left > 0){
        pthread_cond_wait(&aufgabe.mutex_cond_var, &aufgabe.mutex_chances_left);
    }
    pthread_mutex_unlock(&aufgabe.mutex_chances_left);
    
    print_field(&aufgabe);
    print_results(&aufgabe);
}

/* SON FUNCTION --------------------------------------------------------------------- */
void* son (void *son_arg){

    coordinates field_coordinates_to_check;
    int chances = aufgabe.chance;
    int field_status;

    /* Cast thread id */
    long tid;
    tid = (long) son_arg;

    while ( chances > 0 ){
        
        sleep(1);

        /* Generate random coordinates */
        generate_coordinates(&field_coordinates_to_check, aufgabe.dimension_X, aufgabe.dimension_Y);

        /* Block mutex and check state of field */
        pthread_mutex_lock(&aufgabe.mutex_array);
        
            field_status = check_coordinates(&field_coordinates_to_check, aufgabe.fields);

            if ( field_status == 0 ){
                printf("%s\n", "Found!!!");
                /* Take over field */
                aufgabe.fields[field_coordinates_to_check.dimension_X][field_coordinates_to_check.dimension_Y] = 1;
                /* Increment result */
                aufgabe.result[tid-1]++;

                printf("%s%ld%s%d\n", "Id: ", tid-1, " result:", aufgabe.result[tid-1]);
                printf("%d%s%d\n", field_coordinates_to_check.dimension_X, " ", field_coordinates_to_check.dimension_Y);
                print_field(&aufgabe);
            }
            else{
                printf("%s\n", "Missed!!!");
                chances--;
                printf("%s%d\n", "number of chances left: ", chances);
                
            }

        /* Unblock mutex */
        pthread_mutex_unlock(&aufgabe.mutex_array);

        printf("%s\n", "End line");
    }

    /* If chances equal 0 send signal- no chances left */
    pthread_barrier_wait(&aufgabe.barrier);

    pthread_mutex_lock(&aufgabe.mutex_chances_left);
    aufgabe.sons_left = 0;
    pthread_cond_signal(&aufgabe.mutex_cond_var);
    pthread_mutex_unlock(&aufgabe.mutex_chances_left);
}



int main (int argc, char *argv[]){

    initialiesierung_aufgabe(&aufgabe, &argv[1], &argv[2], &argv[3], &argv[4]);

    int rc;

    print_field(&aufgabe);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    threads = ( pthread_t* ) malloc((aufgabe.sons + 1) * sizeof(pthread_t));
    threads[0] = 0;

    /* CREATE REJENT ------------------------------------------ */
    rc = pthread_create(&threads[0], NULL, rejent, (void *) &threads[0]);
    if (rc){
            printf("ERROR; return code 22 from pthread_create() is %d\n", rc);
            exit(-1);
    }

    /* CREATE SONS ---------------------------------------------- */
    for ( int i = 1; i < aufgabe.sons+1; ++i ){
        threads[i] = i;
        rc = pthread_create(&threads[i], NULL, son, (void *) (threads[i]));
          if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for ( int i = 0; i < aufgabe.sons; ++i ){
        pthread_join(threads[i],NULL);
    }

    delete_aufgabe();
    free(threads);

    return 0;
}