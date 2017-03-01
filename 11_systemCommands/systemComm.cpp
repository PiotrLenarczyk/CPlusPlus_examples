#include "headers.h"

int main()
{
    if ( system(  "touch log.txt && rm log.txt && nproc >> log.txt" ) != 0 ) return -1;
    string name = "log.txt";
    ifstream ist( name.c_str() );
    if ( !ist )
    {
        cerr << "File input error!: " << name << " !" << endl;
        return -1;
    }
    int procTH;
    while ( ( ist >> procTH ) && ( ist.good() ) ) { /*...*/ }
    cout << "CPU threads count: " << procTH << endl;

    if ( fileExists( "log.txt" ) ) { if ( system(  "rm log.txt && lscpu >> log.txt" ) != 0 ) return -1; }
    else { if ( system(  "lscpu >> log.txt" ) != 0 ) return -1; }
    string line;
    vector < string > commRead;
    ifstream myfile ("log.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            commRead.push_back( line );
        }
        myfile.close();
    }
    else cout << "Unable to open file"; 
    cout << commRead[1] << endl;

    return 0;
}

