/*************************************************************************
	> File Name: 2.vtable.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 29 Dec 2022 02:08:38 PM UTC
 ************************************************************************/

#include<iostream>
using namespace std;
#define BEGINS(x) namespace x {
#define ENDS(x) }
BEGINS(test1)
//虚函数表给类的大小带来的变化
class Base {
public:
    virtual ~Base() {}
};
class A : public Base {
public:
    int x;
};
class B {
public:
    int x;
};

int main() {
    cout << "sizeof(Base) =" << sizeof(Base) << endl;
    cout << "sizeof(A)    =" << sizeof(A) << endl;
    cout << "sizeof(B)    =" << sizeof(B) << endl;
    return 0;
}
ENDS(test1)

BEGINS(test2)
class Base {
public:
    virtual void func(int x) {
        cout << this << " : class Base : " << x << endl;
    }
    virtual ~Base() {}
};
class A : public Base {
public:
    void func(int x) override {
        cout << this << " : class A : " << x << endl;
        cout << "this->x" << " : class A : " << this->x << endl;
    }
    int x;
};
typedef void (*func)(void *, int);

int main() {
    A a, b;
    a.x = 1000;
    b.x = 10000;
    a.func(123);
    ((func **)(&a))[0][0](&a, 123);
    ((func **)(&a))[0][0](&b, 123);
    return 0;
}
ENDS(test2)


int main() {
    // test1::main();
    test2::main();
    return 0;
}
