////https://gist.github.com/goblinhack/ca81294d76228de61d5199891a6abcc9
#define _POSIX_C_SOURCE 200101L
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#define FUNC_CAST(s)	(void*(*)(void*))&s

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
						f_out_size = stdout_size - 1;
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
						f_out_size = stderr_size - 1;
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
    sprintf( stderr, "ERROR : command \"%s\"\ttimeout'ed after %.0f[ms]", cmd_in, (double)timeout_ms );
    kill( slave_pid, SIGTERM );
    return (ETIMEDOUT);
}

struct Def_systemt
{
	//function pointer
	int(*systemt_ptr)(int, const char*, char*, int, char*, int);
	//function arguments
	int timeout_ms;
	const char *cmd_in;
	char *stdout; 	int stdout_size;
	char *stderr; 	int stderr_size;
	//initializer list
	Def_systemt(
		int(*init_systemt_ptr)(int, const char*, char*, int, char*, int),
		int init_timeout_ms,
		const char *init_cmd_in,
		char *init_stdout, 	int init_stdout_size,
		char *init_stderr, 	int init_stderr_size
	):
		systemt_ptr(init_systemt_ptr),
		timeout_ms(init_timeout_ms),
		cmd_in(init_cmd_in),
		stdout(init_stdout),	stdout_size(init_stdout_size),
		stderr(init_stderr),	stderr_size(init_stderr_size)
	{
	};
};

bool async_systemt_completed = false;
int async_systemt_ret_val = 0;
void async_systemt_caller( Def_systemt *s_in )
{
	async_systemt_completed = false;
		async_systemt_ret_val = s_in->systemt_ptr(
					s_in->timeout_ms,
					s_in->cmd_in,
					s_in->stdout, s_in->stdout_size,
					s_in->stderr, s_in->stderr_size
		);
	async_systemt_completed = true;
};

//function implements background system() with timeout and STD OUT/ERR
//provides tool for periodic procedure execution
int async_systemt(	int timeout_ms, const char *cmd_in, 
					char *stdout, int stdout_size, 
					char *stderr, int stderr_size )
{
	int st;
	pthread_t t_async;
	Def_systemt *systemt_data = 
		new Def_systemt(
			systemt,
			timeout_ms,
			cmd_in, 
			stdout, stdout_size,
			stderr, stderr_size
		);
		st = pthread_create(
				&t_async, NULL,
				FUNC_CAST( async_systemt_caller ),
				systemt_data
			);
		while(async_systemt_completed != true)
		{
			usleep( 100 * 1000 ); //[ms]
			//periodic procedure
			printf( "systemt() executes in background...\n" );
		};
		async_systemt_completed = false;
		pthread_join( t_async, NULL );
	delete(systemt_data);
	return async_systemt_ret_val;
};

int main (void)
{
	int st; 
	char stdout[ 2048 ], stderr[ 2048 ];
	int t = 1400;
	const char cmd_in[] = "echo a && sleep 2 && echoerr b";   

    
	printf("SYNCHRONOUS EXECUTION:\ncmd : \"%s\"\n\n", cmd_in);
    st = systemt(t, cmd_in, stdout, sizeof(stdout), stderr, sizeof(stderr));  
    printf( "STDOUT: \n\"%s\"\n\n", stdout );
    printf( "STDERR: \n\"%s\"c\n\n", stderr );
    if ( st == ETIMEDOUT )
		printf( "Program timeout'ed after %i[s]\n", t );
	else
		printf( "Program executed with status: %i\n", st );
	
	
	printf("\n\n\n\n\n");
		
		
	printf("ASYNCHRONOUS EXECUTION:\ncmd : \"%s\"\n\n", cmd_in);
    st = async_systemt(t, cmd_in, stdout, sizeof(stdout), stderr, sizeof(stderr));  
    printf( "STDOUT: \n\"%s\"\n\n", stdout );
    printf( "STDERR: \n\"%s\"c\n\n", stderr );
    if ( st == ETIMEDOUT )
		printf( "Program timeout'ed after %i[s]\n", t );
	else
		printf( "Program executed with status: %i\n", st );
    return st;
}
