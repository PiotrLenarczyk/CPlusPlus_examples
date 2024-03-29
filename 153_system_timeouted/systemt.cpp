////https://gist.github.com/goblinhack/ca81294d76228de61d5199891a6abcc9
#define _POSIX_C_SOURCE 200101L
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

//Function executes system command with timeout and provides STDERR/OUT
int systemt(int timeout_ms, const char *cmd_in, 
			char *stdout, int stdout_size, 
			char *stderr, int stderr_size)
{
	int timeout_ns = timeout_ms * 1000, poll_ns = (timeout_ms / 100) * 1000;
    pid_t slave_pid;
    const char stdoutfile[] = "/tmp/systemt_stdout.txt";
    const char stderrfile[] = "/tmp/systemt_stderr.txt";
    const char shell[] = "/bin/sh", shell_arg[] = "-c";
    int st, status, cnt = 0, w, outfd, errfd;
    FILE *f_out, *f_err;
	long f_out_size, f_err_size;
    

	if ((slave_pid = fork()) == 0) 
	{
		/*slave thread*/
		remove(stdoutfile);
		remove(stderrfile);
		outfd = open(stdoutfile, O_CREAT|O_WRONLY|O_TRUNC, 0644);
		errfd = open(stderrfile, O_CREAT|O_WRONLY|O_TRUNC, 0644);
		if (!outfd) return EXIT_FAILURE;
		if (!errfd) return EXIT_FAILURE;
		//duplicate program file descriptor and redirect stdout/stderr to file
		dup2(outfd, 1); 
		dup2(errfd, 2);
		close(outfd);
		close(errfd);
		//execute cmd with STDERR/OUT redirection
		execlp( shell, shell, shell_arg, cmd_in );
		_exit(EXIT_FAILURE);
	}

    if (slave_pid <= 0) 
        return (ENOMEM);

    /*master thread*/
    do
    {
        /* Do not want to rely on signals as that could modify
         * the behavior of the invoking application. */
        w = waitpid(slave_pid, &status, WNOHANG);
        if (w == -1) 
            return (EINVAL);

        usleep(poll_ns);
        if (w) 
        {
            if (WIFEXITED(status)) 
            {
				//read STDOUT file content
				f_out = fopen( stdoutfile, "r" );
				if ((f_out != NULL) && (stdout != nullptr))
				{
					fseek( f_out, 0, SEEK_END );
					f_out_size = ftell(f_out);
					rewind(f_out);
					if ( f_out_size > stdout_size )
						f_out_size = stdout_size;
					st = fread( stdout, 1, f_out_size, f_out );
					stdout[f_out_size] = 0; 
					fclose(f_out);
				}else 
				{
					stdout[0] = 0;
				};
				//read STDERR file content
				f_err = fopen( stderrfile, "r" );
				if ((f_err != NULL) && (stderr != nullptr))
				{
					fseek( f_out, 0, SEEK_END );
					f_out_size = ftell(f_out);
					rewind(f_out);
					if ( f_out_size > stderr_size )
						f_out_size = stderr_size;
					st = fread( stderr, 1, f_out_size, f_out );
					stderr[f_out_size] = 0; 
					fclose(f_out);
				}
                //printf("Exited by signal %d\n", WEXITSTATUS(status));
                return (WEXITSTATUS(status));
            }
        }
    } while (cnt++ < (timeout_ns / poll_ns));

    //printf("Timedout kill(%i)\n", slave_pid);
    stdout[0] = 0;
    sprintf( stderr, "ERROR : command \"%s\" timeout'ed after %.0f[ms]", cmd_in, (double)timeout_ms );
    kill( slave_pid, SIGTERM );
    return (ETIMEDOUT);
}

int main (void)
{
	int st; 
	char stdout[ 2048 ], stderr[ 2048 ];
	int t = 1400;
	const char cmd_in[] = "echo a && sleep 2 && echoerr b";   

    
    
    st = systemt(t, cmd_in, stdout, sizeof(stdout), stderr, sizeof(stderr));
    
    
    
    printf( "\"%s\" STDOUT: \n%s\n\n", cmd_in, stdout );
    printf( "\"%s\" STDERR: \n%s\n\n", cmd_in, stderr );
    if ( st == ETIMEDOUT )
		printf( "Program timeout'ed after %i[s]\n", t );
	else
		printf( "Program executed with status: %i\n", st );
		
    return st;
}
