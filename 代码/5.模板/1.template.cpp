/*************************************************************************
	> File Name: 1.template.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 31 Dec 2022 02:08:04 AM UTC
 ************************************************************************/

#include<iostream>
using namespace std;
#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1) 
template<typename T>//希望抽象化出来的类型：
T add(T a, T b) {
    return a + b;
}
int main() {
    cout << "add(3, 4) = " << add(3, 4) << endl;
    cout << "add(3.1, 4.2) = " << add(3.1, 4.2) << endl;
    cout << "add(3, 4.2) = " << add<double>(3, 4.2) << endl;
    return 0;
}
ENDS(test1)

BEGINS(test2) 
class A {
public:
    A() = delete;
    A(int x) : x(x) {}
    int x;
};

class B {
public:
    B() = delete;
    B(int x) : x(x) {}
    int x;
};
class C {
public:
    C() = delete;
    C(int x) : x(x) {}
    int x;
};
C operator+(const A &a, const B &b) {
    return C(a.x + b.x);
}
C operator+(const B &b, const A &a) {
    return C(a.x + b.x);
}
ostream &operator<<(ostream &out, const C &c) {
    out << "Class C.x = " << c.x;
    return out;
}
template<typename T, typename U>//希望抽象化出来的类型：
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}
template<typename T>
void judge(T a) {
    cout << "unknown type" << endl;
    return ;
}
template<>
void judge(int a) {
    cout << "int type" << endl;
    return ;
}
template<>
void judge(double a) {
    cout << "double type" << endl;
    return ;
}

int main() {
    cout << "add(3, 4) = " << add(3, 4) << endl;
    cout << "add(3.1, 4.2) = " << add(3.1, 4.2) << endl;
    cout << "add(3, 4.2) = " << add(3, 4.2) << endl;
    cout << "add(4.2, 3) = " << add(4.2, 3) << endl;
    A a(56);
    B b(78);
    cout << "add(A, B) = " << add(a, b) << endl;
    do {
        decltype(3 + 4.2) a;
        decltype(4.2 + 3) b;
        decltype(3 + 4)   c;
        decltype(string("abc") + string("def")) d;
        judge(a), judge(b), judge(c), judge(d);
    } while(0);
    return 0;
}
ENDS(test2)

BEGINS(test3)
//可以打印任意类型的模板类的函数对象：
template<typename T>
class PrintAny {
public:
    PrintAny(ostream &out) : out(out) {}
    PrintAny &Print(T a) {
        out << a;
        return *this;
    }
    PrintAny &endl() {
        cout << std::endl;
        return *this;
    }
private:
    ostream &out;
};

int main() {
    PrintAny<int> pint(cout);
    PrintAny<double> pdouble(cout);
    PrintAny<string> pstring(cout);
    pint.Print(3).endl();
    pdouble.Print(3.3).endl();
    pstring.Print("hello world").endl();
    return 0;
}
ENDS(test3)

BEGINS(test4)
//可以打印任意类型的模板类的函数对象：
class PrintAny {
public:
    PrintAny(ostream &out) : out(out) {}
    template<typename T>
    PrintAny &Print(T a) {
        out << a;
        return *this;
    }
    PrintAny &endl() {
        cout << std::endl;
        return *this;
    }
private:
    ostream &out;
};

int main() {
    PrintAny p(cout);
    p.Print(3).endl().Print(3.3).endl().Print("hello world").endl();
    return 0;
}
ENDS(test4)

int main() {
    // test1::main();
    // test2::main();
    // test3::main();
    test4::main();
    return 0;
}
