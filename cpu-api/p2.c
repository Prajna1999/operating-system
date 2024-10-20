#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int rc = fork();

    if (rc < 0)
    {
        fprintf(stderr, "fork failed \n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child: redirect the standard output to a file
        close(STDOUT_FILENO);
        open("output.c", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

        // now exec wc
        char *myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("p2.c");
        myargs[2] = NULL;
        execvp(myargs[0], myargs);
    }
    else
    {
        int wc = wait(NULL);
        assert(wc >= 0);
    }
    return 0;
}