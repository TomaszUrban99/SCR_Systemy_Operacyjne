#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]){
	if (argc < 2 ){
		fprintf(stderr, "%s\n", "Not enough arguments");
		return -1;
	}

	/* Contains pipe file descriptors */
	int fd[2], status;
	if (pipe(fd) < 0){
		fprintf(stderr, "%s\n", "Failed to create pipe");
		return -1;
	}

	int pid = fork();

	if (pid == 0){
		printf("%s\n", "This is a child");
		close(0);
		dup(fd[0]);
		close(fd[1]);
		execlp("display","display","-update","1",NULL);
		close(fd[0]);
	}
	else{
		printf("%s\n", "This is a parent");
		close(fd[0]);
		
		int licz = 0;

		int input_fd;
		input_fd = open(argv[1], O_RDONLY);
		
		char buff2[10];
		
		while(licz = read(input_fd, buff2, sizeof(buff2)) > 0){
			write(fd[1],buff2,sizeof(buff2));
		}
		close(fd[1]);
	}
	return 0;
}
