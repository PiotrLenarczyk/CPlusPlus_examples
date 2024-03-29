////https://gist.github.com/goblinhack/ca81294d76228de61d5199891a6abcc9
//#include <string.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <stdio.h>
//#include <errno.h>
//#include <stdarg.h>
//#include <sys/wait.h>

////Function executes system command with timeout and provides STDERR/OUT
//int systemt(int timeout_ms, const char *cmd_in, char *output, int output_size)
//{
	//int timeout_ns = timeout_ms * 1000, poll_ns = (timeout_ms / 100) * 1000;
    //pid_t slave_pid;
    //const char logfile[] = "/tmp/systemt_log.txt";
    //const char shell[] = "/bin/sh", shell_arg[] = "-c";
    //char cmd[2048];
    //int st, status, cnt = 0, w;
    //FILE *f;
	//long f_size;
    

	//if ((slave_pid = fork()) == 0) 
	//{
		///*slave thread*/
		//memset( cmd, 0, sizeof(cmd) );
		////execute cmd with STDERR/OUT redirection
		////sprintf( cmd, " %s &>> %s", cmd_in, logfile );
		////printf( "cmd : %s\n", cmd ); 
		////execlp( shell, shell, shell_arg, cmd );
		//execlp( shell, shell, shell_arg, cmd_in );
		//_exit(EXIT_FAILURE);
	//}

    //if (slave_pid <= 0) 
        //return (ENOMEM);

    ///*master thread*/
    //do
    //{
        ///*
         //* Do not want to rely on signals as that could modify
         //* the behavior of the invoking application.
         //*/
        //w = waitpid(slave_pid, &status, WNOHANG);
        //if (w == -1) 
            //return (EINVAL);

        //usleep(poll_ns);

        //if (w) 
        //{
            //if (WIFEXITED(status)) 
            //{
				////read file content
				//f = fopen( logfile, "r" );
				//if (f != NULL)
				//{
					//fseek( f, 0, SEEK_END );
					//f_size = ftell(f);
					//rewind(f);
					//if ( f_size > output_size )
						//f_size = output_size;
					//st = fread( output, 1, f_size, f );
					//output[f_size] = 0; 
					//fclose(f);
				//}else
				//{
					//output[0] = 0;
				//};
				
                ////printf("Exited by signal %d\n", WEXITSTATUS(status));
                //return (WEXITSTATUS(status));
            //}
        //}
    //} while (cnt++ < (timeout_ns / poll_ns));

    ////printf("Timedout kill(%i)\n", slave_pid);
    //kill( slave_pid, SIGTERM );
    //return (ETIMEDOUT);
//}

//int main (void)
//{
	//int st;
	//int t = 2100;
	//const char cmd_in[] = "blkid";
	//char cmd_out[ 2048 ];
    
    //st = systemt(t, cmd_in, cmd_out, sizeof(cmd_out));
    //printf( "%s : \n%s\n\n", cmd_in, cmd_out );
    //if ( st == ETIMEDOUT )
		//printf( "Program timeout'ed after %i[s]\n", t );
	//else
		//printf( "Program executed with status: %i\n", st );
		
    //return st;
//}

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
    if (!outfd)
    {
        perror("open");
        return EXIT_FAILURE;
    }
    dup2(outfd, 1); // replace stdout
    close(outfd);
    int errfd = open("stderr.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    if (!errfd)
    {
        perror("open");
        return EXIT_FAILURE;
    }
    dup2(errfd, 2); // replace stderr
    close(errfd);
    execlp("/bin/sh", "/bin/sh", "-c", "echo a && sleep 2 && echoerr b");
}

