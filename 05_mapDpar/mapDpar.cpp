//STL
#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h> //int rand()

using namespace std;

int main()
{
//..................... EXAMPLE DATA INPUT .......................    
//type: pointscloud as vectors [ dimX, dimY, dimZ, pointValue ]
//					 sample format: X-dim, Y-dim, Z-dim, value
	vector < float > vecXYZvalTmp( 4, 0.0f );
//											//10 samples dataVector:
	vector < vector < float > > vecXYZval( 10, vecXYZvalTmp );
	for ( unsigned int ySample = 0; ySample < vecXYZval.size(); ySample++ )
	{
		for ( unsigned int xXYZval = 0; xXYZval < vecXYZvalTmp.size(); xXYZval++ )
		{
			vecXYZval[ ySample ][ xXYZval ] = float ( rand() % 155 );
			cout << "vec[" << ySample << "][" << xXYZval << "]:" << vecXYZval[ ySample ][ xXYZval ] << endl;
		}
	}
//...............................................................
        //sorted insertion lowers further data races
	map< float, float > map1D; //[ X-dim, value ]
	map< float, float > map2D; //[ Y-dim, value ]
	map< float, float > map3D; //[ Z-dim, value ]
	map< float, float > mapVal; //[ value, sampleNumber ]
	float valTmp = 0.0f; 
	for ( unsigned int ySample = 0; ySample < vecXYZval.size(); ySample++ )
	{
		valTmp = vecXYZval[ ySample ][ 3 ];
		map1D.insert( pair< float, float >( vecXYZval[ ySample ][ 0 ], valTmp ) );
		map2D.insert( pair< float, float >( vecXYZval[ ySample ][ 1 ], valTmp ) );
		map3D.insert( pair< float, float >( vecXYZval[ ySample ][ 2 ], valTmp ) );
		mapVal.insert( pair< float, float >( valTmp, ( float )ySample ) );
	}
	cout << "==========================================\n";
        cout << "== sorted in dimensions and values =======\n";
	cout << "==========================================\n";
	map< float, float >::iterator mapDiter = map1D.begin();
	for ( unsigned int yTmp = 0; yTmp < vecXYZval.size(); yTmp++ )
	{
		cout << "X[" << yTmp << "]: " << mapDiter->first << endl;
		mapDiter++;
	}
	cout << "\n";
	
	int ind = 0;
	for ( auto& Y: map2D )
	{
		cout << "Y[" << ind << "]: " << Y.first << endl;
		ind++;
	}
	cout << "\n";

	ind = 0;
	for ( auto& Z: map3D )
	{
		cout << "Z[" << ind << "]: " << Z.first << endl;
		ind++;
	}
	
	cout << "\n";
	ind = 0;
	for ( auto& val: mapVal )
	{
		cout << "val[" << ind << "]: " << val.first << " (sampleNo=" << val.second << ")" << endl;
		ind++;
	}
	cout << "\nFurther data processing...\n";
	cout << "==========================================\n";
        cout << "Trivials: \n";
        cout << "1) median is a medium index vector value;\n";
        cout << "2) weight centre is a mean of dimenions and values medians\n";

        return 0;
}

