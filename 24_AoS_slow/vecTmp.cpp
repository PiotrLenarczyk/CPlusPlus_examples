#include <vector>
#include <iostream>

using namespace std;

unsigned int y, x;

struct PointXYZ //slow AoS ( each basic data chunk is small - low any memory bandwidth usage )
{//useful for abstract datastructures f.e. complex
    float X = 0;
    float Y = 0;
    float Z = 0;
    unsigned int varNo = 3;
};

int main()
{
    PointXYZ pickedPointTmp;
    vector < PointXYZ > pickedPointsTmp( 6, pickedPointTmp );
    pickedPointsTmp[ 1 ].X = 1.1f;
    for ( y = 0; y < pickedPointsTmp.size(); y++ )
    {
            cout << "pickedPointsTmp[y=" << y << "][x]: " 
                 << pickedPointsTmp[ y ].X << endl;
            cout << "pickedPointsTmp[y=" << y << "][y]: " 
                 << pickedPointsTmp[ y ].Y << endl;
            cout << "pickedPointsTmp[y=" << y << "][z]: " 
                 << pickedPointsTmp[ y ].Z << endl;                 
    }
    
    cout << "Row-major order:\n";
    for ( y = 0; y < pickedPointsTmp.size(); y++ )
        printf( "pickedPointsTmp[y=%i]: [ %f, %f, %f ]\n", y,
                pickedPointsTmp[ y ].X, pickedPointsTmp[ y ].Y, pickedPointsTmp[ y ].Z  );
    
    return 0;
}
