/*************************************************************************
	> File Name: 10.default_delete.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 25 Dec 2022 05:28:50 AM UTC
 ************************************************************************/

#include<iostream>
using namespace std;

class A {
public:
    A() = default;
    A(const A &) = default;
    A(const A &) {}
};



int main() {
    
    return 0;
}
