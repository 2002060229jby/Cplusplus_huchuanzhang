/*************************************************************************
	> File Name: 7.const_method.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Oct 2022 09:24:38 AM UTC
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1)
class A {
public:
    A() { x = 23800; }
    void say() const {
        x = 30000;
        cout << x << endl;
    }
    mutable int x;
};
void main() {
    const A a;
    a.say();
    return ;
}
ENDS(test1)

int main() {
    test1::main(); 

    return 0;
}
