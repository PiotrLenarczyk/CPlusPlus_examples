//STL
#include <iostream>
#include <stdlib.h> //system
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
//                    //system getrandom():
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <syscall.h>
#include <errno.h>
#include <linux/random.h>

using namespace std;

struct Procs
{
    int procsTH;
    Procs( int uC ) :procsTH( uC ) { }
};

bool fileExists(const char *filename)
{
    ifstream ifile(filename);
    if ( ifile )
        return true;
    else 
        return false;
}
