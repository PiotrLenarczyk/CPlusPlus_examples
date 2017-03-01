#include "headers.h"

int main()
{
    clock_t t, t1;
    t = clock();
    vector< float > vec( 40100, 3.1f );
    cout << "Sum: " << parallel_sum( vec.begin(), vec.end() ) << endl;
    t1 = clock() - t;
    cout << "Time of sequential calculations: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    return 0;
}
