#include <cstdio> 
#include <cstdlib>
#include <cstring>
#include <unistd.h>


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
int main( int argc, char* argv[] )
{	
	int st, period;
	char monitored_processName[1024]; 
	char cmd[2048];
	int pid;
	if(argc != 3)
	{
		printf( "Program-watchdog for monitoring other software\n" );
		printf( "usage:\n" );
		printf( "\t%s processName period_ms\n", argv[0] );
		printf( "f.e.\t%s software.out 100\n", argv[0] );
		return 0;
	};
	
	printf( "argv[2] : \"%s\"\n", argv[2] );
	strcpy( monitored_processName, argv[1] ); 
	period = (int)strtoull( argv[2], NULL, 10 );
	while( 1 )
	{
		pid = pidof( monitored_processName );
		printf( "\"%s\".pid : %i\n", monitored_processName, pid );
		if(pid == 0)
		{
			printf( "\n\n====\n" );
			printf( "\tMonitored program \"%s\"", monitored_processName );
			printf( "is not executing. " );
			printf( "It will be rerun\n====\n\n\n" );
			sprintf( cmd, "./%s", monitored_processName );
			st = system( cmd );
		};
		usleep( period * 1000 );
	};
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
