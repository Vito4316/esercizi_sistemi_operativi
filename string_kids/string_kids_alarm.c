#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

#define DEBUG 0

int curr_nchild = 0;
int *child;

void handler(int signal_type);
void set_signal(void (*foo)(int), int signal_type);
int create_and_exec_child();

int main(int argc, char **argv)
{
    int num_child, i, child_val, pid = getpid();
    char string[1000];
    int stringsize = 0, acc = 0;
    if (argc < 2)
    {
        printf("Argomenti!\n");
        exit(-1);
    }

    num_child = atoi(argv[1]);
    child = malloc(sizeof(*child) * num_child);

    for (i = 0; i < num_child; i++)
        if(create_and_exec_child() == 0)
            exit(-1);

    set_signal(handler, SIGALRM);

    while (1)
    {
        alarm(1);
        while (wait(&child_val) != -1)
        {
            child_val = WEXITSTATUS(child_val);
            string[stringsize++] = (char)child_val;
            acc += child_val;

            printf("string:");
            printf("%s\n", string);
            printf("\nacc:%d\n", acc);

            if (acc % 10 == 0)
            {
                while (curr_nchild > 0)
                {
                    handler(0); //kills random child
                    wait(&child_val);
                    child_val = WEXITSTATUS(child_val);
                    string[stringsize++] = (char)child_val;
                }
                printf("string:");
                printf("%s\n", string);
            }
            else
                create_and_exec_child();
        }
        if (curr_nchild <= 0)
        {
            printf("parent ended\n");
            free(child);
            free(string);
            exit(0);
        }
    }
}

void handler(int signal_type)
{
    if (curr_nchild == 0)
        return;
    int child_to_kill = rand() % curr_nchild;
    int err;

    #ifdef DEBUG
    printf("\n%d\n", curr_nchild);
    for(int i = 0; i < curr_nchild; i++)
        printf("%d\n", child[i]);
    printf("\n\n"); 
    #endif

    printf("Trying to kill child %d, pid: %d\n", child_to_kill, child[child_to_kill]);
    err = kill(child[child_to_kill], SIGINT);
    if (!err); // printf("child killed\n");
    else
    {
        printf("Cannot kill child %d, error\n", child[child_to_kill]);
        exit(-1);
    }

    // swapping chosen child with last member
    curr_nchild--;
    child[child_to_kill] = child[curr_nchild];
}

int create_and_exec_child()
{
    if ((child[curr_nchild] = fork()) != 0)
    {
        printf("Forked child %d\n", child[curr_nchild]);
        curr_nchild++;
        return 1;
    }

    char **vars = malloc(sizeof(char *) * 3);
    vars[0] = "char_loop";
    vars[1] = malloc(sizeof(char));
    srand(getpid());
    vars[1][0] = rand() % (126 - 33) + 33;
    vars[2] = NULL;
    execve("char_loop", vars, NULL);

    return 0;
}

void set_signal(void (*foo)(int), int signal_type)
{
    struct sigaction s_signal;
    bzero(&s_signal, sizeof(struct sigaction));
    s_signal.sa_handler = foo;
    sigaction(signal_type, &s_signal, NULL);
}