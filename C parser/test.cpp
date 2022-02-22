#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

class A
{

public:
   virtual void zar(int x){std::cout << "hi";}
    void foo(int x){ this-> x = x;}
    void bar(int z) {std::cout << "karen";}
private:
    int x;
    int y;
};

class B :public A
{
public:
    int qar(){std::cout << "B";return 1;}
    void mar(){std::cout << "B_mar";}
    void zar(int x){std::cout << "by";}
private:
    int z;
    int t;
};


int main() {
B b;
A c;
b.mar();
A* ptr = &b;
  ptr->zar(5);

    return 0;
}
