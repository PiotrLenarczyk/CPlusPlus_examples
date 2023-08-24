#include <cstdio> 
#include <cstdlib>
#include <cstring>

int pidof( char *processName )
{
	char cmd[1024];
	char pidline[1024];
	char *pid;
	int i = 0, pids_count = 0;
	int pidno[64];
	FILE *fp = NULL;
	memset( pidline, 0, sizeof(pidline) );
	memset( pidno, 0, sizeof(pidno) );
	sprintf( cmd, "pidof %s", processName );
	
	fp = popen(cmd,"r");
	pid = fgets(pidline,1024,fp);
	pid = strtok (pidline," ");
	while(pid != NULL)
	{
		pidno[i] = atoi(pid);
		pid = strtok (NULL , " ");
		i++;
	};
	pids_count = i;
	if ( pids_count > 1 )
		printf( "Found multiple pid's\n" );

	pclose(fp);
	return pidno[0];
};//pidof()

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	
	char processName[] = "bash";
	int pid = pidof( processName );
	printf( "\"%s\".pid : %i\n", processName, pid );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
