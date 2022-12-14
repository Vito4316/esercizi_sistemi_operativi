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

typedef union u_pipe{
    int buff[2];
    struct {
        int read, write;
        int in_open, out_open;
    };
} t_pipe;

int ppid, mod;
t_pipe first;

void pipe_close(t_pipe* p) {
    if(p->in_open) close(p->read);
    p->in_open = 0;
    if(p->out_open) close(p->write);
    p->out_open = 0;
}

void pipe_closeread(t_pipe* p) {
    if(p->in_open == 0)
        dprintf(2, "ERROR! Pipe in already closed, PID: %d\n", getpid());
    close(p->read);
    p->in_open = 0;
}

void pipe_closewrite(t_pipe* p) {
    if(p->out_open == 0)
        dprintf(2, "ERROR! Pipe out already closed, PID: %d\n", getpid());
    close(p->write);
    p->out_open = 0;
}

t_pipe pipe_init() {
    t_pipe x;
    pipe(x.buff);
    if(errno != 0) printf("Pipe creation error: %d\n", errno);
    //else printf("New pipe: write %d read %d\n", x.write, x.read);
    x.in_open = 1;
    x.out_open = 1;
    return x;
}

t_pipe pipe_emptyinit() {
    t_pipe x;
    bzero(&x, sizeof(x));
    x.in_open = 0;
    x.out_open = 0;
    return x;
}

void pipe_setread(t_pipe* p, int in) {
    p->read = in;
    p->in_open = 1;
}

void pipe_setwrite(t_pipe* p, int out) {
    p->write = out;
    p->out_open = 1;
}

/*returns true if successful, false if not */

int pipe_write(t_pipe p, void* elem, size_t size) {
    if(p.out_open)
        return size == write(p.write, elem, size);
    dprintf(2, "ERROR! WRITING TO CLOSED PIPE!\n");
}

int pipe_read(t_pipe p, void* elem, size_t size) {
    if(p.in_open)
        return size == read(p.read, elem, size);
    dprintf(2, "ERROR! READING CLOSED PIPE!\n");
}

void run_child(t_pipe my_pipe) {
    int n;
    int flag = 1;
    while(flag) {
        if(pipe_read(my_pipe, &n, sizeof(n))) {
            printf("PID: %d, read: %d\n", getpid(), n);
        }
        else {
            printf("PID: %d ERROR! Could not read, err: %d\n", getpid(), errno);
            exit(-1);
        }
    
        if(n == 0) {
            if(pipe_write(my_pipe, &n, sizeof(n)));
            else printf("PID: %d ERROR! Could not write termination value\n", getpid());
            pipe_close(&my_pipe);
            exit(0);
        }
        else n--;
        
        if(pipe_write(my_pipe, &n, sizeof(n))) {
            printf("PID: %d, write: %d\n", getpid(), n);
        }
        else {
            printf("PID: %d ERROR! Could not write\n", getpid());
            exit(-1);
        }
    }
    exit(-1);
}

void recursive_fork_piped_child(int read, int num) {
    t_pipe new_pipe;
    if(num == 0) {
        if(fork() == 0) {
            new_pipe = pipe_emptyinit();   
            pipe_setread(&new_pipe, read);
            pipe_closeread(&first);
            pipe_setwrite(&new_pipe, first.write);
            run_child(new_pipe);
            exit(0);
        }
        return;
    }

    new_pipe = pipe_init();

    if(fork() == 0) {
        if(read != first.read) pipe_close(&first);
        else pipe_closewrite(&first);
        pipe_closeread(&new_pipe);
        pipe_setread(&new_pipe, read);
        run_child(new_pipe);
        exit(0);
    }

    if(read != first.read) close(read);
    pipe_closewrite(&new_pipe);
    recursive_fork_piped_child(new_pipe.read, num-1);
    //pipe_closeread(&new_pipe);
    return; 
}

int main(int argc, char** argv) {
    if(argc < 3) {
        printf("argomenti!");
        exit(0);
    }

    int num_child = atoi(argv[1]);
    mod = atoi(argv[2]);
    int i=0;
    ppid = getpid();
    
    /* setting first pipe */
    first = pipe_init();
    recursive_fork_piped_child(first.read, num_child);
    
    printf("Parent writing %d\n", mod);
    if(pipe_write(first, &mod, sizeof(mod)) == sizeof(mod)) 
        printf("Parent written %d\n", mod);
    pipe_close(&first);
    while(wait(NULL) != -1);
    printf("All child are dead!\n");
    exit(0);    
}