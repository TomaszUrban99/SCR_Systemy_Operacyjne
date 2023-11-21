#include <stdio.h>
#include <string.h>

/* 
    This code is based on code from the book
    Advanced Linux Programming
    available on OReilly platform.
*/

float get_cpu_speed (){

    char buffer[200000];
    int bytes_read;
    float clock_speed;

    FILE *file_handle = fopen("/proc/cpuinfo", "r");

    if (file_handle==NULL){
        printf("Tus");
        return -1;
    }
        

    bytes_read = fread(buffer, 1, sizeof(buffer), file_handle);

    if ( bytes_read == 0 || sizeof(buffer) == bytes_read){
        return -1;
    }
        

    buffer[bytes_read] = '\0';

    /* Close input stream */
    fclose(file_handle);

    char *match = strstr(buffer, "cpu MHz");
    if (match == NULL)
        return -1;
    
    
    sscanf(match, "cpu MHz :%f", &clock_speed);
  
    return clock_speed;
}

int main()
{
    float clock_speed = get_cpu_speed();

    printf("%f%s", clock_speed, "\n");

    if ( clock_speed < 0)
        return -1;

    printf("%s%f%s", "Cpu speed: ", clock_speed, "\n");

    return 0;
}

