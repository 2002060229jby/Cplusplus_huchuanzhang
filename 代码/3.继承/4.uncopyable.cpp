/*************************************************************************
	> File Name: 4.uncopyable.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 29 Dec 2022 10:29:00 AM UTC
 ************************************************************************/

#include<iostream>
using namespace std;
#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1)
//设计一个不能被拷贝的功能类；（拷贝构造+赋值运算）
class UNCOPYABLE {
public:
    UNCOPYABLE(const UNCOPYABLE &) = delete;
    UNCOPYABLE &operator=(const UNCOPYABLE &) = delete;
    UNCOPYABLE &operator=(const UNCOPYABLE &) const = delete;
protected:
    UNCOPYABLE() = default;
};
class A : public UNCOPYABLE {};

int main() {
    A a;
    A b;
    // b = a;  // no, operator= delete
    // A b(a); // no, copy constructor delete
    return 0;
}
ENDS(test1)


BEGINS(test2)
class HAS_XY {
public:
    int x, y;
};

class HAS_XYZ : public HAS_XY {
public:
    int z;
}; 

class A : public HAS_XY {
public:
    A() { x = y = 1; }
};
class B : public HAS_XY {
public:
    B() { x = y = 2; }
};
class C : public HAS_XYZ {
public:
    C() { x = y = z = 3; }
};
class D : public HAS_XY {
public:
    D() { x = y = 4; }
};
class E : public HAS_XYZ {
public:
    E() { x = y = z = 5; }
};

void func(HAS_XY &a) {
    cout << "has xy : ";
    cout << a.x << ", " << a.y << endl;
    return ;
}

void func(HAS_XYZ &a) {
    cout << "has xyz";
    cout << a.x << ", " << a.y << ", " << a.z << endl;
    return ;
}
int main() {
    A a;
    B b;
    C c;
    D d;
    E e;
    func(a), func(b), func(c), func(d), func(e);
    return 0;
}
ENDS(test2)

int main() {
    test2::main();
    return 0;
}
