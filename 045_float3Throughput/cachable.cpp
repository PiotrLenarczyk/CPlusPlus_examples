//STL
#include <chrono>
#include <vector>
#include <random>
#include <iostream> 

using std::vector; using std::cout; using std::endl;

std::default_random_engine gen;
std::uniform_real_distribution< float > randf( 0.0f, 1.0f );
struct float3
{
    float x;
    float y;
    float z;
};
const unsigned N = 1E6; 
size_t i = 0;
long tDif = 0;
vector < float3 > vecAoS( N ); float3 f3;
vector < float > vec3N( 3*N );
vector < float > vecX( N ); vector < float > vecY( N ); vector < float > vecZ( N );
vector < vector < float > > vec2D( 3, vecX );

int main( void )
{
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();
    t1 = std::chrono::high_resolution_clock::now();
    for ( i = 0; i < N; i++ )
    {
        f3.x = randf( gen );
        f3.y = randf( gen );
        f3.z = randf( gen );
        vecAoS[ i ] = f3;
    }
    t2 = std::chrono::high_resolution_clock::now();
    tDif = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
    cout << "vecAoS throughput: "
              << double( N ) / ( double( tDif ) / 1E9 )
              << " [float3/s]\n";
    
              
    t1 = std::chrono::high_resolution_clock::now();
    for ( i = 0; i < N; i += 3 )
        for ( size_t xyz = 0; xyz < 3; xyz++ )
        {
            vec3N[ i + xyz ] = randf( gen );
        }
    t2 = std::chrono::high_resolution_clock::now();
    tDif = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
    cout << "vec3N throughput: "
              << double( N ) / ( double( tDif ) / 1E9 )
              << " [float3/s]\n";
    
              
    t1 = std::chrono::high_resolution_clock::now();
    for ( i = 0; i < N; i ++ )
    {
        vecX[ i ] = randf( gen );
        vecY[ i ] = randf( gen );
        vecZ[ i ] = randf( gen );
    }
    t2 = std::chrono::high_resolution_clock::now();
    tDif = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
    cout << "vecX vecY vecZ throughput: "
              << double( N ) / ( double( tDif ) / 1E9 )
              << " [float3/s]\n";
              
    t1 = std::chrono::high_resolution_clock::now();
    for ( i = 0; i < N; i += 3 )
        for ( size_t xyz = 0; xyz < 3; xyz++ )
        {
            vec2D[ xyz ][ i ] = randf( gen );
        }
    t2 = std::chrono::high_resolution_clock::now();
    tDif = std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count();
    cout << "vector< vector < float > > throughput: "
              << double( N ) / ( double( tDif ) / 1E9 )
              << " [float3/s]\n";
              
    return 0;
}

//P.S. Sequentially it is acceptable efficient.
