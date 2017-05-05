//STL
#include <iostream>
#include <time.h>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
using namespace std;
unsigned i, no( 8000 );
float val = 17.31f;
clock_t t;
vector < float > vecPopulate( no, val );
/*
 17.31f FLOAT datatype containers comparision:
    -vector
    -list
    -map
    -multimap
    -unordered_map
    -unordered_multimap
    -set
    -multiset
    -unordered_set
    -unordered_multiset
 1) static and dynamic containers comparision
 2) global and local containers - GLOBALS ARE POPULATED AT STARTUP
 3) nested with static vector < float >
 4) set vs dynamic vector & sort(); populated with rand()
 */ 




int main( void )
{
    cout << endl << endl << "1) static and dynamic containers comparision" << endl;
    t = clock();
    vector < float > vecStat( no, val );
    cout << "static vector CPU clocks: " << clock() - t << endl;
    t = clock();
    vector < float > vecDyn;
    for ( i = 0; i < no; i++ )
        vecDyn.push_back( val );
    cout << "dynamic vector CPU clocks: " << clock() - t << endl;
    t = clock();
    list < float > lisStat( no, val );
    cout << "static list CPU clocks: " << clock() - t << endl;
    t = clock();
    list < float > listDyn;
    for ( i = 0; i < no; i++ )
        listDyn.push_back( val );
    cout << "dynamic list CPU clocks: " << clock() - t << endl;
    t = clock();
    map< unsigned, float > mapDyn;
    for ( i = 0; i < no; i++ )
        mapDyn.insert( make_pair( i, val ) );
    cout << "dynamic map CPU clocks: " << clock() - t << endl;
    t = clock();
    multimap< unsigned, float > mmapDyn;
    for ( i = 0; i < no; i++ )
        mmapDyn.insert( make_pair( i, val ) );
    cout << "dynamic multimap CPU clocks: " << clock() - t << endl;
    t = clock();
    unordered_map< unsigned, float > un_mapDyn;
    for ( i = 0; i < no; i++ )
        un_mapDyn.insert( make_pair( i, val ) );
    cout << "dynamic unordered_map CPU clocks: " << clock() - t << endl;
    t = clock();
    unordered_map< unsigned, float > un_mmapDyn;
    for ( i = 0; i < no; i++ )
        un_mmapDyn.insert( make_pair( i, val ) );
    cout << "dynamic unordered_multimap CPU clocks: " << clock() - t << endl;
    t = clock();
    set< float > s;
    for ( i = 0; i < no; i++ )
        s.insert( val );
    cout << "dynamic set CPU clocks: " << clock() - t << endl;
    t = clock();
    multiset< float > mset;
    for ( i = 0; i < no; i++ )
        mset.insert( val );
    cout << "dynamic multiset CPU clocks: " << clock() - t << endl;
    t = clock();
    unordered_set< float > un_s;
    for ( i = 0; i < no; i++ )
        un_s.insert( val );
    cout << "dynamic unordered_set CPU clocks: " << clock() - t << endl;
    t = clock();
    unordered_multiset< float > un_mset;
    for ( i = 0; i < no; i++ )
        un_mset.insert( val );
    cout << "dynamic unordered_multiset CPU clocks: " << clock() - t << endl;
    
    cout << endl << endl << "3) nested with static vector < float >" << endl;
    t = clock();
    vector < vector < float > > vecStat3( no, vecPopulate );
    cout << "static nested vector CPU clocks: " << clock() - t << endl;
    t = clock();
    vector < vector < float > > vecDyn3;
    for ( i = 0; i < no; i++ )
        vecDyn3.push_back( vecPopulate );
    cout << "dynamic nested vector CPU clocks: " << clock() - t << endl;
    t = clock();
    list < vector < float > > lisStat3( no, vecPopulate );
    cout << "static nested list CPU clocks: " << clock() - t << endl;
    t = clock();
    list < vector < float > > listDyn3;
    for ( i = 0; i < no; i++ )
        listDyn3.push_back( vecPopulate );
    cout << "dynamic nested list CPU clocks: " << clock() - t << endl;
    t = clock();
    map< unsigned, vector < float > > mapDyn3;
    for ( i = 0; i < no; i++ )
        mapDyn3.insert( make_pair( i, vecPopulate ) );
    cout << "dynamic nested map CPU clocks: " << clock() - t << endl;
    t = clock();
    multimap< unsigned, vector < float > > mmapDyn3;
    for ( i = 0; i < no; i++ )
        mmapDyn3.insert( make_pair( i, vecPopulate ) );
    cout << "dynamic nested multimap CPU clocks: " << clock() - t << endl;
    t = clock();
    unordered_map< unsigned, vector < float > > un_mapDyn3;
    for ( i = 0; i < no; i++ )
        un_mapDyn3.insert( make_pair( i, vecPopulate ) );
    cout << "dynamic nested unordered_map CPU clocks: " << clock() - t << endl;
    t = clock();
    unordered_map< unsigned, vector < float > > un_mmapDyn3;
    for ( i = 0; i < no; i++ )
        un_mmapDyn3.insert( make_pair( i, vecPopulate ) );
    cout << "dynamic nested unordered_multimap CPU clocks: " << clock() - t << endl;
    t = clock();
    set<  vector < float > > s3;
    for ( i = 0; i < no; i++ )
        s3.insert( vecPopulate );
    cout << "dynamic nested set CPU clocks: " << clock() - t << endl;
    t = clock();
    multiset< vector < float > > mset3;
    for ( i = 0; i < no; i++ )
        mset3.insert( vecPopulate );
    cout << "dynamic nested multiset CPU clocks: " << clock() - t << endl;
    
    cout << endl << endl << "4) rand values: map vs dynamic vector & sort()" << endl;
    t = clock();
    vector < float > vecDyn4;
    for ( i = 0; i < no; i++ )
        vecDyn4.push_back( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) );
    sort( vecDyn4.begin(), vecDyn4.end() );
    cout << "rand dynamic vector & sort CPU clocks: " << clock() - t << endl;
    t = clock();
    list < float > lDyn4;
    for ( i = 0; i < no; i++ )
        lDyn4.push_back( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) );
    lDyn4.sort();
    cout << "rand dynamic list & sort CPU clocks: " << clock() - t << endl;
    t = clock();
    set< float > s4;
    for ( i = 0; i < no; i++ )
        s4.insert( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) );
    cout << "rand dynamic set CPU clocks: " << clock() - t << endl;
    t = clock();
    map< float, float > mapDyn4;
    for ( i = 0; i < no; i++ )
        mapDyn4.insert( make_pair( static_cast <float> (rand()) / static_cast <float> (RAND_MAX), val ) );
    cout << "rand dynamic map CPU clocks: " << clock() - t << endl;

    return 0;
}
