//====	libTCC stuff here:
#define DEF 15
int add(int a, int b) 
{	return a + b; 
};
int foobar(int n) 
{   printf("add(%d, %d) = %d\n", n, 2 * n, add(n, 2 * n));
	foo();
	printf( "DEF : %i\n", DEF );
    return 1;
};
//====
