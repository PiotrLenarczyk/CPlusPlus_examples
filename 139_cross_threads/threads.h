//derived from FLTK/test/threads.h
#ifdef __linux
	#include <pthread.h>
	typedef pthread_t Cross_Thread;
	typedef void* (Cross_Thread_Func)( void* );
	typedef pthread_mutex_t Cross_Mutex;
	static int cross_create_thread( 
				Cross_Thread &th, 
				Cross_Thread_Func *f_th, 
				void *f_th_input )
	{	return pthread_create( 
					(Cross_Thread*)&th, 0, f_th, f_th_input );
	};
	
	static void cross_synchronize( Cross_Thread &th )
	{	pthread_join( th, NULL );
	};
	
	void* cross_exit_this_thread( void )
	{	void *th_result;
		th_result = ( void* )NULL;
		pthread_exit( th_result );
		return th_result;
	};
	
	#define CROSS_MUTEX_CREATE( m )									\
				Cross_Mutex m = PTHREAD_MUTEX_INITIALIZER;
	
	#define CROSS_MUTEX_FREE( m )
	
	void cross_lock( Cross_Mutex &m )
	{	pthread_mutex_lock( &m );
	};
	
	void cross_unlock( Cross_Mutex &m )
	{	pthread_mutex_unlock( &m );
	};
		
#elif defined _WIN32
	#include <windows.h>
	#include <process.h>
	typedef HANDLE Cross_Thread;
	typedef void* (__cdecl Cross_Thread_Func)( void* );
	typedef HANDLE Cross_Mutex;
	
	static int cross_create_thread(
				Cross_Thread &th,
				Cross_Thread_Func *f_th,
				void *f_th_input )
	{	th = (Cross_Thread)_beginthread(
				(void( __cdecl* )( void* ))f_th, 4096, f_th_input );//4kiB stack
		return (int)th;
	};
	
	static void cross_synchronize( Cross_Thread &th )
	{	WaitForSingleObject( th, INFINITE );
	};
	
	void* cross_exit_this_thread( void )
	{	_endthread();
		return 0;
	};
	
	#define CROSS_MUTEX_CREATE( m )									\
				Cross_Mutex m = CreateMutex( NULL, FALSE, NULL );
	
	#define CROSS_MUTEX_FREE( m )	CloseHandle( m );

	
	void cross_lock( Cross_Mutex &m )
	{	WaitForSingleObject( m, INFINITE );
	};
	
	void cross_unlock( Cross_Mutex &m )
	{	ReleaseMutex( m );
	};
	
#endif
