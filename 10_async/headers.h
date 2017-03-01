//biblioteka STL
#include <iostream>
#include <vector>
#include <algorithm>
#include <future>
#include <time.h>

using namespace std;

template < typename RAIter >
double parallel_sum( RAIter beg, RAIter end )
{
    auto len = end - beg;
    if( len < 1000 )
        return accumulate( beg, end, 0 );
 
    RAIter mid = beg + len / 2;
    auto handle = async( launch::async, parallel_sum< RAIter >, mid, end );
    double sum = parallel_sum( beg, mid );
    return sum + handle.get();
}
