#define _GNU_SOURCE
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<time.h>
#include<sys/wait.h>
#include<errno.h>

#define IN 0 
#define OUT 1

union pipe{
    int buff[2];
    struct {
        int in, out;
    };
};

int main(int argc, char** argv) {
    if(argc < 3) {
        printf("argomenti!");
        exit(0);
    }

    int num_pipe = atoi(argv[1]);
    int num_child = atoi(argv[1]);
    int mod = atoi(argv[2]);
    int i=0;
    int ppid = getpid();
    

    /* first child*/
    int firstpipe[2];
    int lastpipe[2];
    int newpipe[2];
    int my_in;
    int my_out;

    pipe(firstpipe);
    pipe(newpipe);
    if(fork() == 0) {
        close(firstpipe[OUT]);
        close(newpipe[IN]);
        my_in = firstpipe[IN];
        my_out = newpipe[OUT];
        //dprintf(1, "PID: %d, my in: %d, my out: %d\n", getpid(), my_in, my_out);
    }                       /* father mantains firstpipe[OUT]*/
    /* end first child*/
    else { /*nth child */
        memcpy(lastpipe, newpipe, sizeof(int) * 2);
        for(int i = 1; i < num_child-1; i++) {
            pipe(newpipe);
            dprintf(1, "I am father, %d %d, %d %d\n", lastpipe[IN], lastpipe[OUT], newpipe[IN], newpipe[OUT]);
            if(fork() == 0) { //child
                my_in = lastpipe[IN];
                my_out = newpipe[OUT];
                //dprintf(1, "PID: %d, my in: %d, my out: %d\n", getpid(), my_in, my_out);
                close(newpipe[IN]);
                break;
            }
            if(ppid == getpid()) {
                close(lastpipe[IN]);
                close(lastpipe[OUT]);
                close(newpipe[IN]);
                memcpy(lastpipe, newpipe, sizeof(int) * 2);
            }
        }
            /* last child*/
        if(ppid == getpid()){
            if(fork() == 0) {
                my_in = lastpipe[IN];
                my_out = firstpipe[OUT];
                close(lastpipe[OUT]);
                close(firstpipe[IN]);
                //dprintf(1, "PID: %d, my in: %d, my out: %d\n", getpid(), my_in, my_out);
            }
            else 
                close(firstpipe[IN]);
        }
    }

    if(getpid() == ppid) {
        int x = write(firstpipe[OUT], &mod, sizeof(int));
        printf("Written %d in pipe %d, err: %d\n", mod, firstpipe[IN], x);
        close(firstpipe[IN]);
        while(wait(NULL) != -1);
        exit(0);
    }

    while(1) {
        int n;
        read(my_in, &n, sizeof(int));
        printf("PID: %d, read: %d\n", getpid(), n);
        if(n == 0) {
            printf("%d exiting", getpid());
            close(my_in);
            close(my_out);
            exit(0);
        }
        n--;
        write(my_out, &n, sizeof(int));
        printf("PID: %d, write: %d\n", getpid(), n);
    }
}