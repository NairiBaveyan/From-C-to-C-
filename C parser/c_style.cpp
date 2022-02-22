#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>


struct A
{

    int x;
    int y;
};

struct B 
{
	A obj;
    int z;
    int t;
};


    void zarA(A *that, int x){std::cout << "hi";}
    void fooA(A *that, int x){ that-> x = x;}
    void barA(A *that, int z) {std::cout << "karen";}
    int qarB (B  *that ){std::cout << "B";return 1;}
    void marB (B  *that ){std::cout << "B_mar";}
    void zarB (B  *that, int x){std::cout << "by";}
struct VTable
{
    void* vPtr;
    std::string type_info;
}vt;

int main() {
B b;
A c;
marB(&b);
vt.vPtr = (void*)&b;
zarB((B*)vt.vPtr,5);

    return 0;
}

