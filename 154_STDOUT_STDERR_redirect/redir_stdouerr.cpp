//https://stackoverflow.com/questions/44221222/how-to-use-execlp-with-redirected-output
#define _POSIX_C_SOURCE 200101L
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int outfd = open("stdout.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    int errfd = open("stderr.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    if (!outfd) return EXIT_FAILURE;
    if (!errfd) return EXIT_FAILURE;
    dup2(outfd, 1); //duplicat program file descriptor and redirect stdout to file
    dup2(errfd, 2); //duplicat program file descriptor and redirect stderr to file
    close(outfd);
    close(errfd);
    execlp("/bin/sh", "/bin/sh", "-c", "echo a && sleep 2 && echoerr b");
}







////Fork-based redirection:
//#define _POSIX_C_SOURCE 200101L
//#include <stdlib.h>
//#include <stdio.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <sys/wait.h>
//#include <fcntl.h>
//#include <unistd.h>

//int main(void)
//{
    //int outfd = open("1.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    //if (!outfd)
    //{
        //perror("open");
        //return EXIT_FAILURE;
    //}
    //pid_t pid = fork();
    //if (pid < 0)
    //{
        //close(outfd);
        //perror("fork");
        //return EXIT_FAILURE;
    //}

    //if (pid)
    //{
        //// child code
        //dup2(outfd, 1); // replace stdout
        //close(outfd);

        //// just a "useless cat" for simplicity:
        //execlp("cat", "cat", "redir.c", 0);
    //}
    //else
    //{
        //// parent code
        //close(outfd);
        //int status;
        //waitpid(pid, &status, 0);
        //if (WIFEXITED(status)) return WEXITSTATUS(status);
        //else return EXIT_FAILURE;
    //}
//}
