//STL
#include <iostream>

using namespace std;

struct MyClass {
  MyClass() { cout << "MyClass constructed\n"; }
  ~MyClass() { cout << "MyClass destroyed\n"; }
};


int main () {
    MyClass *pt;
    pt = new MyClass[ 3 ]; //also: MyClass *pt = new MyClass[ 3 ];
    delete[] pt;

    return 0;
}
