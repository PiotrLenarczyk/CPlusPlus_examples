//https://gist.github.com/goblinhack/ca81294d76228de61d5199891a6abcc9
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>

int
execl_timed (int timeout_ms,
             int poll_ms,
             int argin,
             const char *cmd, ...)
{
	int timeout_ns = timeout_ms * 1000, poll_ns = poll_ms * 1000;
    pid_t slave_pid;
    char *args[100];
    char *arg;
    const int maxargs = sizeof(args) / sizeof(args[0]);
    int argno = 0;
    va_list ap;
    int status;
    int cnt = 0;
    int w;

    va_start(ap, cmd);

    args[argno++] = (char*) cmd;
    while (argno < argin) {
        arg = va_arg(ap, char *);
        args[argno++] = arg;
        if (!arg) {
            break;
        }
    }
    va_end(ap);

    if (!argno || (argno >= maxargs)) {
        return (EINVAL);
    }

    if ((slave_pid = fork()) == 0) {
        /*
         * child
         */
        //execv(cmd, args);
        printf( "cmd : %s\n", cmd );
        printf( "args[0] : %s\n", args[0] );
        printf( "args[1] : %s\n", args[1] );
        printf( "args[2] : %s\n", args[2] );
        //execlp( cmd, (const char*)args );
       char arg[] = { "echo a && sleep 2 && echo b" };
		execlp( cmd, cmd, "-c", arg );
        _exit(EXIT_FAILURE);
    }

    if (slave_pid <= 0) {
        return (ENOMEM);
    }

    /*
     * master thread
     */
    do {
        /*
         * Do not want to rely on signals as that could modify
         * the behavior of the invoking application.
         */
        w = waitpid(slave_pid, &status, WNOHANG);
        if (w == -1) {
            return (EINVAL);
        }

        usleep(poll_ns);

        if (w) {
            if (WIFEXITED(status)) {
                printf("Exited by signal %d\n", WEXITSTATUS(status));
                return (WEXITSTATUS(status));
            }
        }
    } while (cnt++ < (timeout_ns / poll_ns));

    printf("Timedout kill(%i)\n", slave_pid);
    kill( slave_pid, SIGTERM );
    return (ETIMEDOUT);
}

int main (void)
{
    execl_timed(3000, 100, 4, "/bin/sh", "-c", 
								"echo a && sleep 2 && echo b");
}
