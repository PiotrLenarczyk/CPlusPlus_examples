/* https://thinkingandcomputing.com/posts/using-avx-instructions-in-matrix-multiplication.html */
#include <iostream>
#include <time.h>
using namespace std;

extern "C" {
#include <immintrin.h>
}

int main(){
    clock_t t = clock();
	__m256 ymm0, ymm1;			//define the registers used
	float a[8]={1,2,3,4,5,6,7,8};
	float b[8]={2,3,4,5,6,7,8,9};
	float c[8];
	ymm0 = __builtin_ia32_loadups256(a);	//load the 8 floats in a into ymm0
	ymm1 = __builtin_ia32_loadups256(b);	//load the 8 floats in b into ymm1

	//multiply ymm0 and ymm1, store the result in ymm0
	ymm0 = __builtin_ia32_mulps256(ymm0, ymm1);
	__builtin_ia32_storeups256(c, ymm0);	//copy the 8 floats in ymm0 to c
    cout << "CPU clocks for 8 floats: " << clock() - t << endl;
	for (int i=0; i<8; i++)
		cout<<c[i]<<", ";
    cout << endl;
	return 0;
}
