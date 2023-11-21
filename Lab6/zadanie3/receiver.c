#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define FIFO_PATH "/tmp/fifo1"

int main (int argc, char* argv[]){

	int fifo_fd = open(FIFO_PATH, O_RDONLY);
	
	if (fifo_fd < 0){
		fprintf(stderr, "%s\n", "Failed to open given FIFO");
	}
	char buff[10];
	while(read(fifo_fd,buff,sizeof(buff))>0){
		write(1, buff, sizeof(buff));
	}

	close(fifo_fd);
	return 0;
}
