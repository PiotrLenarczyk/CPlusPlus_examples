#include "headers.h"
 
int main() 
{

//sequential threads costs; data races hazard; erroneous
// thread t1 (f,vec); 

    
//     //adding threads manually
//     A a;
//     thread t1(&A::foo, &a, 100);
//     thread t2(&A::foo, &a, 200);
//     t1.join();
//     t2.join();
    
//  //trivial vector of threads
//     vector<thread> threads;
//     A a;
//     cout << "increase global counter with 10 threads...\n";
//     for (int i=1; i<=10; ++i)
//         threads.push_back(thread(&A::foo, &a, 100));
//     cout << "synchronizing all threads...\n";
//     for (auto& th : threads) th.join();

//  //lambda trivial vector of threads
//     vector<thread> threads;
//     A a;
//     cout << "increase global counter with 10 threads...\n";
//     for (int i=1; i<=10; ++i)
//         threads.push_back(thread([&] { a.foo(100); }));
//     cout << "synchronizing all threads...\n";
//     for (auto& th : threads) th.join();
  
    
//     //  //threads vector
    clock_t t, t1;
    t = clock();
 
    vector<double> vec(10001,1.15);
    for ( int i = 0; i < ( int )vec.size(); i++ )
        vec[ i ] = pow( sqrt( vec[ i ] ), 0.2381 );
    t1 = clock() - t;
    cout << "czas obl. sekw.: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    t = clock();
    if ( vec.size() > ( int )7000 )
    {
        int parts = 2;
        vector< thread > threads( parts );
        vector < B > bVec( parts );
        cout << "calculations with " << parts << " threads...\n";
        int vecPartSize = ( int )( ceil( ( double )vec.size() / parts ) );
        vector < double > vecTmp( vecPartSize, 0 );
        for ( int i = 0; i < parts; i++ )
        {
            for ( int j = 0; j < vecPartSize; j++ )
                if ( i * parts + j < ( int )vec.size() )
                    vecTmp[ j ] = vec[ i * parts + j ];
            bVec[ i ].n = vecTmp;
        }
        for ( int i = 0; i < parts; i++ )
            threads[ i ] = thread( &B::foo, &bVec[ i ] );
        cout << "synchronizing all threads...\n";
        for (auto& th : threads) th.join();
        for ( int i = 0; i < parts; i++ )
            for ( int j = 0; j < vecPartSize; j++ )
                if ( i * parts + j < ( int )vec.size() )
                    vec[ i * parts + j ] = vecTmp[ j ];
    }
    t1 = clock() - t;
    cout << "czas vec<thread>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    int N = 1000;
    vector < vector < float > > firstMat( N );
    vector < vector < float > > secondVecMat( N );
    vector < vector < float > > resultsHostMat( N );
    vector < float > pierwszyVec( N, 3.14 );
    vector < float > drugiVec( N, 2.72 );
    vector < float > wynikHost( N );
    for ( int i = 0; i < N; i++ )
    {
        firstMat[ i ] = pierwszyVec;
        secondVecMat[ i ] = drugiVec;
        resultsHostMat[ i ] = wynikHost;
    }
    
    t = clock();
    for ( int j = 0; j < N; j++ )
        for ( int i = 0; i < N; i++ )
                resultsHostMat[ j ][ i ] = firstMat[ j ][ i ] + secondVecMat[ j ][ i ];    
    t1 = clock() - t;
    cout << "time of CPU sequential calculations " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;

    // (1D1D/2D) vector of vectors + threads 
    t = clock();
    for ( int iVec = 0; iVec < N; iVec++ )
    {
        int parts = 2;
        vector< thread > threads( parts );
        vector < Bsum > bVec( parts );
        int vecPartSize = ( int )( ceil( ( float )firstMat[ iVec ].size() / parts ) );
        vector < float > vecTmp( vecPartSize, 0 );
        for ( int i = 0; i < parts; i++ )
        {
            for ( int j = 0; j < vecPartSize; j++ )
                if ( i * parts + j < ( int )firstMat[ iVec ].size() )
                    vecTmp[ j ] = firstMat[ iVec ][ i * parts + j ];
            bVec[ i ].a = vecTmp;
            for ( int j = 0; j < vecPartSize; j++ )
                if ( i * parts + j < ( int )secondVecMat[ iVec ].size() )
                    vecTmp[ j ] = secondVecMat[ iVec ][ i * parts + j ];
            bVec[ i ].b = vecTmp;
            for ( int j = 0; j < vecPartSize; j++ )
                if ( i * parts + j < ( int )secondVecMat[ iVec ].size() )
                    vecTmp[ j ] = 0;
            bVec[ i ].c = vecTmp;            
        }
        for ( int i = 0; i < parts; i++ )
            threads[ i ] = thread( &Bsum::sum, &bVec[ i ] );
        for (auto& th : threads) th.join();
        for ( int i = 0; i < parts; i++ )
            for ( int j = 0; j < vecPartSize; j++ )
                if ( i * parts + j < ( int )resultsHostMat[ iVec ].size() )                
                    resultsHostMat[ iVec ][ i * parts + j ] = vecTmp[ j ];                    
    }
    t1 = clock() - t;
    cout << "time of vec<vec<>> row-major vec<thread> : " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    return 0;
}
