/*************************************************************************
	> File Name: 5.constructor.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Oct 2022 02:45:58 AM UTC
 ************************************************************************/

#include<iostream>
using namespace std;

class A {
public:
    A(int x) : x(x) {
        cout << this << " : Class A : " << x << endl;
    }
    A(const A &a) {
        cout << this << " copy from " << &a << endl;
    }
    void operator=(const A &a) {
        cout << this << " assign from " << &a << endl;
        return ;
    }
    int x;
};

class B1 {
public:
    B1() = default;
    B1(const B1 &) {
        cout << "B1 copy constructor" << endl;
    }
};

class B2 {
public:
    B2() = default;
    B2(const B2 &) {
        cout << "B2 copy constructor" << endl;
    }
};
class B3 {
public:
    B3() = default;
    B3(const B3 &) {
        cout << "B3 copy constructor" << endl;
    }
};
class B {
public:
    B1 b1;
    B2 b2;
    B3 b3;
};

class Data {
public:
    Data() : __x(0), __y(0), a(34) {
        cout << "default constructor" << endl;
    }
    int x() { return __x; }
    int y() { return __y; }
    ~Data() {
        cout << "destructor" << endl;
    }

private:
    int __x, __y;
    A a;
};


int main() {
    B b1;
    B b2 = b1;

    Data d;
    cout << d.x() << " " << d.y() << endl;
    A a = 45; // 2 constructor 
    cout << "address a : " << &a << endl;
    a = 78;


    return 0;
}


// 类中的四个默认：
// 1. 默认构造
// 2. 默认析构
// 3. 默认拷贝
// 4. 默认赋值运算
