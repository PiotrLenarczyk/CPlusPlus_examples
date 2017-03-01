#include "headers.h"

int main()
{
    clock_t t, t1;
    t = clock();
    long int XY = 14000; 
    long int n = XY * XY;
    cout << "Algorithm differentiates types of data calculation times:" << endl;
    cout << "[ " << XY << ", " << XY << "]; l = " << n << endl;
    cout << "==========================================" << endl;
    cout << " uint8_t / int/ float / double tab[l] too big!" << endl;
    
    cout << "==========================================" << endl;        
    t = clock();
    Matrix< uint8_t, 2 > m2_uint8( XY, XY );
    for ( int x = 0; x < m2_uint8.dim1(); x++ )
		for ( int y = 0; y < m2_uint8.dim2(); y++ )
			m2_uint8( x, y ) = 1;
	t1 = clock() - t;
    cout << "time of Matrix<uint8_t,2>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
  
    t = clock();  
    Matrix< int, 2 > m2_int( XY, XY );
    for ( int x = 0; x < m2_int.dim1(); x++ )
		for ( int y = 0; y < m2_int.dim2(); y++ )
			m2_int( x, y ) = 1;
	t1 = clock() - t;			
    cout << "time of Matrix<int,2>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    t = clock();      
    Matrix< float, 2 > m2_fl( XY, XY );  
    for ( int x = 0; x < m2_fl.dim1(); x++ )
		for ( int y = 0; y < m2_fl.dim2(); y++ )
			m2_fl( x, y ) = 1;
	t1 = clock() - t;			
    cout << "time of Matrix<float,2>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    t = clock();      
    Matrix< double, 2 > m2_d( XY, XY );  
    for ( int x = 0; x < m2_d.dim1(); x++ )
		for ( int y = 0; y < m2_d.dim2(); y++ )
			m2_d( x, y ) = 1;
	t1 = clock() - t;
    cout << "time of Matrix<double,2>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    cout << "==========================================" << endl;
        
    t = clock();              
    vector < uint8_t > vec1D_uint8( n, 1 );
	t1 = clock() - t;
    cout << "time of vec1D<uint8_t>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    t = clock();          
    vector < int > vec1D_int( n, 1 );
    t1 = clock() - t;
    cout << "time of vec1D<int>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    t = clock();          
    vector < float > vec1D_float( n, 1 );
	t1 = clock() - t;    
    cout << "time of vec1D<float>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    t = clock();          
    vector < double > vec1D_double( n, 1 );
	t1 = clock() - t;    
    cout << "time of vec1D<double>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    cout << "==========================================" << endl;
    //on 1E5 error on 16GB RAM i7-5500U 2C/4T
    t = clock();          
    vector < vector < uint8_t > > vec2D_uint8_t( XY ); 
    vector < uint8_t > tmp2( XY, 1 );
    for ( int i = 0; i < XY; i++ )
        vec2D_uint8_t[ i ] = tmp2;
	t1 = clock() - t;        
    cout << "time of vec<vec<uint8_t>>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    t = clock();          
    vector < vector < int > > vec2D_int( XY ); 
    vector < int > tmp( XY, 1 );
    for ( int i = 0; i < XY; i++ )
        vec2D_int[ i ] = tmp;
	t1 = clock() - t;        
    cout << "time of vec<vec<int>>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
        
    t = clock();              
    vector < vector < float > > vec2D_f( XY ); 
    vector < float > tmp3( XY, 1 );
    for ( int i = 0; i < XY; i++ )
        vec2D_f[ i ] = tmp3;
	t1 = clock() - t;        
    cout << "time of vec<vec<float>>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    t = clock();          
    vector < vector < double > > vec2D_d( XY ); 
    vector < double > tmp4( XY, 1 );
    for ( int i = 0; i < XY; i++ )
        vec2D_d[ i ] = tmp4;
	t1 = clock() - t;        
    cout << "time of vec<vec<double>>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    cout << "==========================================" << endl;
    
    t = clock();              
    QVector < uint8_t > qvec1D_uint8( n, 1 );
	t1 = clock() - t;
    cout << "time of QVec1D<uint8_t>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    t = clock();          
    QVector < int > qvec1D_int( n, 1 );
    t1 = clock() - t;
    cout << "time of QVec1D<int>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    t = clock();          
    QVector < float > qvec1D_float( n, 1 );
	t1 = clock() - t;    
    cout << "time of QVec1D<float>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    
    t = clock();          
    QVector < double > qvec1D_double( n, 1 );
	t1 = clock() - t;    
    cout << "time of QVec1D<double>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    cout << "==========================================" << endl;
        
    t = clock();      
    QVector < QVector < uint8_t > > qvec2D_uint8_t; 
    QVector < uint8_t > tmp5( XY, 1 );
    for ( int i = 0; i < XY; i++ )
        qvec2D_uint8_t.push_back( tmp5 );
	t1 = clock() - t;        
    cout << "time of QVec<QVec<uint8_t>>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;

    t = clock();          
    QVector < QVector < int > > qvec2D_int; 
    QVector < int > tmp6( XY, 1 );
    for ( int i = 0; i < XY; i++ )
        qvec2D_int.push_back( tmp6 );
	t1 = clock() - t;        
    cout << "time of QVec<QVec<int>>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;

    t = clock();              
    QVector < QVector < float > > qvec2D_f; 
    QVector < float > tmp7( XY, 1 );
    for ( int i = 0; i < XY; i++ )
        qvec2D_f.push_back( tmp7 );
	t1 = clock() - t;        
    cout << "time of QVec<QVec<float>>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;

    t = clock();              
    QVector < QVector < double > > qvec2D_d; 
    QVector < double > tmp8( XY, 1 );
    for ( int i = 0; i < XY; i++ )
        qvec2D_d.push_back( tmp8 );
	t1 = clock() - t;        
    cout << "time of QVec<QVec<double>>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;

    cout << "==========================================" << endl;

    XY = 140; 
    n = XY * XY * XY;
    cout << "3D [ " << XY << ", " << XY << ", " << XY << "]; l = " << n << endl;
    t = clock();      
    Matrix< double, 3 > m3_d( XY, XY, XY );  
    for ( int x = 0; x < m3_d.dim1(); x++ )
		for ( int y = 0; y < m3_d.dim2(); y++ )
			for ( int z = 0; z < m3_d.dim3(); z++ )
				m3_d( x, y, z ) = 1;
	t1 = clock() - t;
    cout << "time of Matrix<double,3>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;       
      
    t = clock();      
    QVector < QVector < QVector < double > > > qvec3D_d; 
    QVector < QVector < double > > qvec2D_dtmp; 
    QVector < double > tmp9( XY, 1 );
    for ( int i = 0; i < XY; i++ )
        qvec2D_dtmp.push_back( tmp9 );
    for ( int i = 0; i < XY; i++ )
	    qvec3D_d.push_back( qvec2D_dtmp );
	t1 = clock() - t;        
    cout << "time of QVec<QVec<QVec<double>>>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    cout << "==========================================" << endl;

    XY = 14000; 
    n = XY * XY * XY;
    cout << "3D [ " << XY << ", " << XY << ", " << XY << "]; l = " << n << endl;
    t = clock();      
    QVector < QVector < QVector < double > > > qvec3D_d1; 
    QVector < QVector < double > > qvec2D_dtmp1; 
    QVector < double > tmp10( XY, 1 );
    for ( int i = 0; i < XY; i++ )
        qvec2D_dtmp1.push_back( tmp10 );
    for ( int i = 0; i < XY; i++ )
	    qvec3D_d1.push_back( qvec2D_dtmp1 );
	t1 = clock() - t;        
    cout << "time of QVec<QVec<QVec<double>>>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    cout << "==========================================" << endl;
    
    cout << "static 4D" << endl;
    XY = 14000; 
    n = XY * XY * XY * XY;
    cout << "4D [ " << XY << ", " << XY << ", " << XY << ", " << XY << "]; l = " << n << endl;
    t = clock();      
    QVector < QVector < QVector < QVector < double > > > > qvec4D_ds; 
    QVector < QVector < QVector < double > > > qvec3D_dtmps; 
    QVector < QVector < double > > qvec2D_dtmp2s; 
    QVector < double > tmp11( XY, 16.876512 );
    for ( int i = 0; i < XY; i++ )
        qvec2D_dtmp2s.push_back( tmp11 );
    for ( int i = 0; i < XY; i++ )
        qvec3D_dtmps.push_back( qvec2D_dtmp2s );
    for ( int i = 0; i < XY; i++ )
        qvec4D_ds.push_back( qvec3D_dtmps );	    
    t1 = clock() - t;        
    cout << "time of QVec<QVec<QVec<QVec<double>>>>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    cout << "==========================================" << endl;
        
    cout << "dynamic 4D" << endl;        
    XY = 14000; 
    n = XY * XY * XY * XY;
    cout << "4D [ " << XY << ", " << XY << ", " << XY << ", " << XY << "]; l = " << n << endl;
    t = clock();      
    QVector < QVector < QVector < QVector < double > > > > qvec4D_d; 
    QVector < QVector < QVector < double > > > qvec3D_dtmp; 
    QVector < QVector < double > > qvec2D_dtmp2; 
    QVector < double > tmp12( XY, 16.876512 );
    for ( int i = 0; i < XY; i++ )
        qvec2D_dtmp2.push_back( tmp12 );
    for ( int i = 0; i < XY; i++ )
        qvec3D_dtmp.push_back( qvec2D_dtmp2 );
    for ( int i = 0; i < XY; i++ )
        qvec4D_d.push_back( qvec3D_dtmp );	    
    t1 = clock() - t;        
    cout << "time of QVec<QVec<QVec<QVec<double>>>>: " << ((float)(t1))/CLOCKS_PER_SEC << "[s]" << endl;
    cout << "==========================================" << endl;

    return 0;
}

