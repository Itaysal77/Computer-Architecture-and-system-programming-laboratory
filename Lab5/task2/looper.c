#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>


void sigHandler(int sig);

int main(int argc, char **argv){ 

	
	signal(SIGINT,sigHandler);
	signal(SIGTSTP,sigHandler);
	signal(SIGCONT,sigHandler);
	printf("Starting the program\n");
	
	while(1) {
		sleep(2);
	}
	

	return 0;
}
void sigHandler(int sig){
	printf(" Signal %s was recived\n",strsignal(sig));
	fflush(stdout);
	if(sig == SIGTSTP){
		signal(SIGCONT,sigHandler);
	}else if(sig == SIGCONT)
	{
		signal(SIGTSTP,sigHandler);
	}
	signal(sig,SIG_DFL);
	raise(sig);	
}