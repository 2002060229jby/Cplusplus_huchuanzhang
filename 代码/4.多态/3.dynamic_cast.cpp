/*************************************************************************
	> File Name: 3.dynamic_cast.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 30 Dec 2022 01:46:04 AM UTC
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }
BEGINS(test1)
class Base {
public:
    virtual ~Base() {}
};

class A : public Base {};
class B : public Base {};
class C : public Base {};

int main() {
    srand(time(0));
    Base *p;
    switch (rand() % 4) {
        case 0: p = new A(); break;
        case 1: p = new B(); break;
        case 2: p = new C(); break;
        case 3: p = nullptr; break;
    }
    A a;
    if (p) ((void **)(p))[0] = ((void **)(&a))[0];
    if (dynamic_cast<A *>(p) != nullptr) {
        cout << "p pointer A class Object" << endl; 
    } else if (dynamic_cast<B *>(p) != nullptr) {
        cout << "p pointer B class Object" << endl;
    } else if (dynamic_cast<C *>(p) != nullptr) {
        cout << "p pointer C class Object" << endl;
    } else {
        cout << "p is nullptr" << endl;
    }
    return 0;
}
ENDS(test1)


int main() {
    test1::main();
    return 0;
}
