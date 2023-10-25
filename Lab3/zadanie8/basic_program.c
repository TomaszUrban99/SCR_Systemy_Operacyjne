#include <bits/types/sigset_t.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

#define TIME_UNBLOCKED 5

int blocking_signal = 0;

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
	if (blocking_signal == 0)
		blocking_signal = 1;
	else
	 	blocking_signal = 0;
}

int main(int argc, char** argv){

sigset_t signalSet;
sigfillset(&signalSet);
sigdelset(&signalSet,SIGALRM);

struct sigaction sigalrm_struct;
sigalrm_struct.sa_handler = signal_handler_sigalrm;
sigemptyset(&sigalrm_struct.sa_mask);
sigaddset(&sigalrm_struct.sa_mask, SIGALRM);
sigprocmask(SIG_BLOCK, &sigalrm_struct.sa_mask,NULL);
sigaction(SIGALRM,&sigalrm_struct, NULL);

struct sigaction sigterm_struct;
sigterm_struct.sa_handler = signal_handler_sigterm;
sigterm_struct.sa_mask = signalSet;
sigaction(SIGTERM, &sigterm_struct, 0);

struct sigaction sigusr1_struct;
sigusr1_struct.sa_handler = signal_handler_sigusr1;
sigusr1_struct.sa_mask = signalSet;
sigaction(SIGUSR1,&sigusr1_struct,0);

struct sigaction sigusr2_struct;
sigusr2_struct.sa_handler = signal_handler_sigusr2;
sigusr2_struct.sa_mask = signalSet;
sigaction(SIGUSR2,&sigusr2_struct, 0);

sigprocmask(SIG_UNBLOCK,&signalSet,NULL);

int i = 0;
while(1){
	++i;
	if ( blocking_signal == 1){
		sigprocmask(SIG_BLOCK,&signalSet,NULL);
		printf("%s","...\n");
		sleep(1);
	if(i%10 == 1){
		printf("%s\n","Unblocking incoming signals");
		sigprocmask(SIG_UNBLOCK,&signalSet,NULL);
		sleep(TIME_UNBLOCKED);
		printf("%s\n", "Blocking incoming signals");
		sigprocmask(SIG_BLOCK,&signalSet,NULL);
		}
	}
	else
		sigprocmask(SIG_UNBLOCK,&signalSet,NULL);
}

return 0;
}
