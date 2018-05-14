//STL
#include <iostream>
#include <math.h>

using namespace std;

int main()
{
//===========================================================================================
	register float bestMatch; //it is not a CPU register variable!!!
	bestMatch = 14.1;
	cout << "bestMatch: " << bestMatch << endl;
	cout << "&bestMatch: " << &bestMatch << endl; // bestMatch is an ordinary variable

//===========================================================================================
	typedef long long Out; //long long datatype declaration
	volatile Out out,tmp;
	Out register rax asm("rax"); //declaration of using 64bit register (CPU: x64, x86 )
	asm volatile("rdtsc":"=A"(rax)); //sth register; rdtsc counts clocks CPU;
	out = out * tmp + rax; //rand values processing
	cout << "out.rand: " << out << endl;
	out = 0; 
	cout << "out: " << out << endl;
	cout << "&out: " << &out << endl; //register-type address
	volatile Out i;
	i = 66000;
	cout << "i: " << i << endl;
	cout << "&i: " << &i << endl; 

	volatile Out fi;
	fi = 7.32;	//intigers register
	cout << "fi: " << fi << endl;
//==========================================================================================
	typedef float floatReg; //float datatype declaration
	volatile floatReg bestMatchReg; //every operation on bestMatchReg variable will be 
                                        //executed on floatReg register
	floatReg register floatRax asm( "xmm0" ); //register declaration SMM ( SIMD ) 128bit
// 	floatReg register floatRax asm( "ymm0" ); //as mentioned above: register declaration AVX 256bit
	asm volatile( "rdtsc" : "=A" (floatRax) ); 
	bestMatchReg = 3.141592;
	cout << "bestMatchReg: " << bestMatchReg << endl;
	cout << "&bestMatchReg: " << &bestMatchReg << endl;
	bestMatchReg = pow( bestMatchReg, 3 );
	cout << "bestMatchReg^3: " << bestMatchReg << endl;
	volatile floatReg inszyF;
	inszyF = 101.2;
	cout << "inszyF: " << inszyF << endl;
	cout << "&inszyF: " << &inszyF << endl;

	return 0;
}

