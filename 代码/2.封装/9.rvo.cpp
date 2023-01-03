/*************************************************************************
	> File Name: 9.rvo.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 25 Dec 2022 05:12:34 AM UTC
 ************************************************************************/

#include<iostream>
using namespace std;
class A {
public:
    A() {
        cout << this << ": default constructor" << endl;
    }
    A(int x) {
        cout << this << ": param constructor" << endl;
    }
    A(const A &a) {
        cout << this << ": copy constructor" << endl;
    }
};

A func() {
    A temp(3);
    cout << "object temp: " << &temp << endl;
    return temp;
}

int main() {
    A a = func();
    cout << "object a: " << &a << endl;

    return 0;
}
