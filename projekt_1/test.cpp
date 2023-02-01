#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <stack>
#include <typeinfo>

using namespace std;

class A {
public:
    int x;
    int y;
    A(int a, int b) : x(a), y(b) {}
    inline bool operator==(const A &l, const A &r) {
    if(l.x == l.x && l.y == r.y) { return true; }
    else { return false; }
    }
};

int main() {
A a(1,2);
A b(1,3);
if(a==b) { cout<<"TAK"<<endl; }
else { cout<<"NIE"<<endl; }

return 0;
}
