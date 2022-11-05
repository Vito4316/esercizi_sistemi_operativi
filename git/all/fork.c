#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main(){
	int pid;
	
	pid = fork();
	
	for(int i = 0; i < 100; i++) {
		printf("%d\n", i);
		sleep(1);
		if(pid != 0)
			exit(0);
	}
}
