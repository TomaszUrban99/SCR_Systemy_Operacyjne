#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define FIFO_PATH "/tmp/fifo1"
#define TIME_WAIT 5

int main (int argc, char *argv[]){
	int time = TIME_WAIT;
	if (argc < 2 ){
		fprintf(stderr, "%s\n", "Not enough arguments");
		return -1;
	}

	printf("%s\n", "This is a source");
	printf("%s\n", "Creating FIFO");

	if ( mkfifo(FIFO_PATH, 0777) == -1){
		if ( errno != EEXIST ){
		fprintf(stderr, "%s\n", "Failed to create FIFO");
		return -1;
		}
	}
	
	/* OPEN FIFO */
	int fifo_fd = open(FIFO_PATH, O_WRONLY);

	for ( int i = 1; i < argc; ++i){
		int input_fd = open(argv[i], O_RDONLY);
		int licz = 0;
		char buff[10];
		
		while(licz = read(input_fd, buff, sizeof(buff)) > 0){
			write(fifo_fd,buff, sizeof(buff));
		}
		printf("%s\n", "Koniec pliku");
		close(input_fd);
		sleep(TIME_WAIT);
	}
	
	printf("%s\n", "Koniec");
	close(fifo_fd);	

	return 0;
}
