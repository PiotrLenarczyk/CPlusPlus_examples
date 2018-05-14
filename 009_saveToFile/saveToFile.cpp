//STL
#include <string>
#include <fstream>

using namespace std;

int main ()
{
  ofstream ofs;
  ofs.open ( "test.txt", ofstream::out | ofstream::app );

  ofs << 1.1f << " " << 2.2f << " " << 1.3f << "\n";
  ofs << to_string( 1.1f ) << " " << to_string( 2.2f ) << " " << to_string( 1.3f ) << "\n";
  ofs.close();

  return 0;
}
