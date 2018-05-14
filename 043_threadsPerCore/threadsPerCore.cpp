//STL
#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <math.h>
#include <chrono>

using namespace std;

unsigned NTh = 0;
float u = 0.0f;
unsigned long int tDif;
const unsigned mSize = 1E4;
unsigned iTh = 0;
void mapPopulate( map <unsigned, float> *mIn );
void mathCount( float in, float &out ); 

int main( void )
{
    for ( NTh = 1; NTh < 512; NTh += 32 )
    {
        auto t1 = std::chrono::high_resolution_clock::now();

        map <unsigned, float> mTmp;
        vector < map <unsigned, float> > mVec( NTh, mTmp );
        vector < thread > thVec;
        for ( iTh = 0; iTh < NTh; iTh++ )
            thVec.push_back( thread( mapPopulate, &mVec[ iTh ] ) );
        for ( iTh = 0; iTh < NTh; iTh++ )
            thVec[ iTh ].join();
        auto t2 = std::chrono::high_resolution_clock::now(); //highest possible standard chronometrics
        tDif = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
        u = float( tDif ) / float( mSize * NTh );
        std::cout << "efficiency th[ " << NTh << "]: "
                << u
                << "\n";
    }
    
    cout << "===================================================================\n";
    cout << "======== fine grained for 1- 32 threads per core =======\n";
    cout << "===================================================================\n";
    for ( NTh = 1; NTh < 32; NTh++ )
    {
        auto t1 = std::chrono::high_resolution_clock::now();

        map <unsigned, float> mTmp;
        vector < map <unsigned, float> > mVec( NTh, mTmp );
        vector < thread > thVec;
        for ( iTh = 0; iTh < NTh; iTh++ )
            thVec.push_back( thread( mapPopulate, &mVec[ iTh ] ) );
        for ( iTh = 0; iTh < NTh; iTh++ )
            thVec[ iTh ].join();
        auto t2 = std::chrono::high_resolution_clock::now(); //highest possible standard chronometrics
        tDif = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
        u = float( tDif ) / float( mSize * NTh );
        std::cout << "efficiency th[ " << NTh << "]: "
                << u
                << "\n";
    }
    cout << "=========================================\n";
    cout << "I am a newbie, but 16 threads per isolated core looks good!\n";
    
    return 0;
}

void mapPopulate( map <unsigned, float> *mIn )
{
    unsigned uintTmp;
    float fTmp;
    for ( unsigned i = 0; i < mSize; i++ )
    {
        uintTmp = i;
        mathCount( uintTmp, fTmp );
        mIn->insert( make_pair( i, fTmp ) );
    }
}

void mathCount( float in, float &out )
{
    out = 0.1f * in;
}
