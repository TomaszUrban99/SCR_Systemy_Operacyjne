#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

#define TIME_UNBLOCKED 5

int blocking_signal_change = 0;
int signal_release = 0;
int signal_blocking_enable = 0;

void signal_handler_sigalrm(int signal_parameter){
	return;
}

void signal_handler_sigterm(int signal_parameter){
	printf("%s\n", "Closing...");
	exit(0);
}

void signal_handler_sigusr1(int signal_parameter){
	printf("%s\n", "Back to work");
	return;
}

void signal_handler_sigusr2(int signal_parameter){
	
		blocking_signal_change = 1;

		if ( signal_blocking_enable == 1)
			signal_blocking_enable = 0;
		else
			signal_blocking_enable = 1;

		if ( signal_release == 0)
			signal_release = 1;
		else
			signal_release = 0;
}

int main(int argc, char** argv){

sigset_t signalSet;
sigset_t signalSet_old;

/* Fill set with all signals */
sigfillset(&signalSet);
sigemptyset(&signalSet_old);

struct sigaction sigalrm_struct;
sigalrm_struct.sa_handler = SIG_IGN;
sigaction(SIGALRM,&sigalrm_struct, NULL);

struct sigaction sigterm_struct;
sigterm_struct.sa_handler = signal_handler_sigterm;
sigaction(SIGTERM, &sigterm_struct, 0);

struct sigaction sigusr1_struct;
sigusr1_struct.sa_handler = signal_handler_sigusr1;
sigaction(SIGUSR1,&sigusr1_struct,0);

struct sigaction sigusr2_struct;
sigusr2_struct.sa_handler = signal_handler_sigusr2;
sigaction(SIGUSR2,&sigusr2_struct, 0);

/*sigprocmask(SIG_UNBLOCK,&signalSet, &signalSet_old);*/

int i = 0;

while(1){
	
	++i;

	if ( signal_blocking_enable == 1){
	if(i%10 == 1){
		blocking_signal_change = 1;
		signal_release = 1;
	}
	
	if(i%10 == 6){
		blocking_signal_change = 1;
		signal_release = 0;
	}

	if ( blocking_signal_change == 1 ){

		if (signal_release == 1){
			printf("%s\n","Unblocking incoming signals");
			sigprocmask(SIG_UNBLOCK,&signalSet,NULL);
		}
		else{
			printf("%s\n", "Blocking incoming signals");
		 	sigprocmask(SIG_BLOCK, &signalSet, NULL);
		}

		blocking_signal_change = 0;

	}
	}

	sleep(1);
		
}

return 0;
}
