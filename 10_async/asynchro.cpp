#include "headers.h"

int main()
{
    clock_t t, t1;
    vector< float > vec( 40100, 3.1f );
    double result = vec.size() * vec[ 0 ];
    t = clock();
    double resSeq = 0.0;
    for ( uint i = 0; i < vec.size(); i++ )
        resSeq += vec[ i ];
    cout << "Sum: " << resSeq << "; err = " << result - resSeq << " ( " << ( result - resSeq ) / result << "[%] )" << endl;
    t1 = clock() - t;
    cout << "Time of sequential calculations: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    t = clock();
    double resPar = parallel_sum( vec.begin(), vec.end() );
    cout << "Sum: " << resPar << "; err = " << result - resPar << " ( " << ( result - resPar ) / result << "[%] )" << endl;
    t1 = clock() - t;
    cout << "Time of parallel calculations: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    return 0;
}
