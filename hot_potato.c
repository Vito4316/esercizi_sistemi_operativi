#define _GNU_SOURCE
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<time.h>
#include<sys/wait.h>
#include<errno.h>

#define IS_FATHER() (getpid() == ppid)
#define IN 0 
#define OUT 1

int stop = 1;
int ppid;

typedef union u_pipe{
    int buff[2];
    struct {
        int in, out;
        int in_open, out_open;
    };
} t_pipe;

void pipe_close(t_pipe* p) {
    close(p->in);
    p->in_open = 0;
    close(p->out);
    p->out_open = 0;
}

void pipe_closein(t_pipe* p) {
    if(p->in_open == 0)
        dprintf(2, "ERROR! Pipe in already closed, PID: %d\n", getpid());
    close(p->in);
    p->in_open = 0;
}

void pipe_closeout(t_pipe* p) {
    if(p->out_open == 0)
        dprintf(2, "ERROR! Pipe out already closed, PID: %d\n", getpid());
    close(p->out);
    p->out_open = 0;
}

t_pipe pipe_init() {
    t_pipe x;
    pipe(x.buff);
    x.in_open = 1;
    x.out_open = 1;
    return x;
}

void pipe_setin(t_pipe* p, int in) {
    p->in = in;
    p->in_open = 1;
}

void pipe_setout(t_pipe* p, int out) {
    p->out = out;
    p->out_open = 1;
}

int pipe_write(t_pipe p, void* elem, size_t size) {
    if(p.out_open)
        return write(p.out, elem, size);
    dprintf(2, "ERROR! WRITING TO CLOSED PIPE!\n");
}

int pipe_read(t_pipe p, void* elem, size_t size) {
    if(p.in_open)
        return read(p.in, elem, size);
    dprintf(2, "ERROR! READING CLOSED PIPE!\n");
}

void run_piped_child(int in, int out, int i, int* unwanted, int un_size) {
    if(fork() != 0) return;
    t_pipe my_pipe = pipe_init();
    pipe_setin(&my_pipe, in);
    pipe_setout(&my_pipe, out);
    printf("Child %d, PID: %d generated\n", i, getpid());
    int j;
    for(j = 0; j < un_size; j++) close(unwanted[i]);


    /* synchronization */
    printf("Child %d, PID: %d generated, entering in sleep\n", i, getpid());
    while(stop) pause();
    printf("Child %d, PID: %d woken up\n", i, getpid());

    while(1) {
        int n;
        if(pipe_read(my_pipe, &n, sizeof(n)) == sizeof(n)) printf("PID: %d, read: %d\n", getpid(), n);
        else {
            printf("child %d, PID: %d ERROR! Could not read\n", i, getpid());
            exit(-1);
        }
        if(n == 0) {
            printf("%d ended\n", getpid());
            pipe_write(my_pipe, &n, sizeof(n));
            pipe_close(&my_pipe);
            exit(0);
        }
        n--;
        if(pipe_write(my_pipe, &n, sizeof(n)) == sizeof(n)) printf("PID: %d, write: %d\n", getpid(), n);
        else {
            printf("child %d, PID: %d ERROR! Could not write\n", i, getpid());
            exit(-1);
        }
    }
    exit(-1);
}

void handler_custom(int sig);

int main(int argc, char** argv) {
    if(argc < 3) {
        printf("argomenti!");
        exit(0);
    }

    int num_child = atoi(argv[1]);
    int mod = atoi(argv[2]);
    int i=0;
    ppid = getpid();
    int unw[2];

	/*SET HANDLER*/
	struct sigaction sighandler;
	bzero(&sighandler, sizeof(sighandler));
	sighandler.sa_handler = &handler_custom;
	sigaction(SIGUSR1, &sighandler, NULL);
    
    /* setting pipes */
    t_pipe firstpipe = pipe_init();
    t_pipe newpipe;
    t_pipe oldpipe;

    for(i = 0; i < num_child; i++) {
        newpipe = pipe_init();
    
        if(i == 0) {
            unw[0] = firstpipe.out;
            unw[1] = newpipe.in;
            run_piped_child(firstpipe.in, newpipe.out, i, unw, 2);
            pipe_closeout(&newpipe);
        }
        else if(i == num_child-1) {
            unw[0] = oldpipe.in;
            unw[1] = firstpipe.out;
            run_piped_child(oldpipe.in, firstpipe.out, i, unw, 2);
            pipe_closein(&oldpipe);
        }
        else {
            unw[0] = oldpipe.out;
            unw[1] = newpipe.in;
            run_piped_child(oldpipe.in, newpipe.out, i, unw, 2);
            pipe_closein(&oldpipe);   
            pipe_closeout(&newpipe);
        }

        oldpipe = newpipe;
    }

    pipe_close(&oldpipe);

    kill(0, SIGUSR1);

    if(pipe_write(firstpipe, &mod, sizeof(mod)) == sizeof(mod)) 
        printf("Written %d\n", mod);
    pipe_close(&firstpipe);
    while(wait(NULL) != -1);
    exit(0);    
}

void handler_custom(int signum) {
    if(signum == SIGUSR1 && ppid != getpid()){ /*CHILD CONT*/
		stop=0;
	}
}