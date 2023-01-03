/*************************************************************************
	> File Name: 12.friend.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 25 Dec 2022 09:32:47 AM UTC
 ************************************************************************/

#include<iostream>
#include<cstdlib>
#include<functional>
using namespace std;
//输出点类的对象信息
//1. 类内
//2. 类外：友元

#define BEGINS(x) namespace x {    
#define ENDS(x) }

BEGINS(haizei)
class Point;
ENDS(haizei)

BEGINS(array_object)
class Array {
public:
    Array(int n = 100) : n(n), data(new int[n]) {}
    int &operator[](int ind) {
        return data[ind];
    }
    const int &operator[](int ind) const {
        return data[ind];
    }//返回值是const类型的保证不会被修改。
    int operator[](const char *s) {
        int ind = stoi(s);
        return data[ind];
    }
    int &operator[](const haizei::Point &a); 
private:
    int n;
    int *data;
};
ENDS(array_object)

BEGINS(haizei)
class Point {
public:
    Point(int x, int y) : x(x), y(y) {
        z1 = rand();
        z2 = z1 + 1;
        z3 = z2 + 1;
        cout << this << "rand value : " << z1 << endl;
    }
    void output() {
        cout << "inner : " << x << " " << y << endl;
    }
    friend void output(Point &); // 类外的output函数是友元
    friend ostream &operator<<(ostream &, const Point &);
    friend Point operator+(const Point &, const Point &);
    friend int &array_object::Array::operator[](const Point &);
    Point operator+(int n) const {
        return Point(x + n, y + n);
    }
    Point &operator+=(int x) {
        this->x += x;
        this->y += x;
        return *this;
    }
    Point operator++(int) {//返回加一之前的那个值,所以不传引用
        Point ret(*this);
        x++;
        y++;
        return ret;
    }
    Point &operator++() { 
        x++;
        y++;
        return *this;
    }
    int z1, z2, z3;

private:
    int x, y;
};
void output(Point &a) {
    cout << "outer : " << a.x << " " << a.y <<endl;
}
ostream &operator<<(ostream &out, const Point &p) {
    out << "Point(" << p.x << ", " << p.y << ")";
    return out;
}
Point operator+(const Point &a, const Point &b) {
    return Point(a.x + b.x, a.y + b.y);
}
ENDS(haizei)

BEGINS(test1)
using namespace haizei;
int main() {
    srand(time(0));
    Point p(3, 4), q(5, 6); 
    p.output();
    output(p);
    cout << p << endl;
    cout << (p + q) << endl;
    cout << (p + 5) << endl;
    cout << (p + (p + q)) << endl;
    // p + 5 => p.operator+(5)
    const Point cp(7, 8);
    cout << (cp + 6) << endl;

    Point *pp = &p;
    int Point::* px = &Point::z1;
    // 表示这是一个Point类的,int类型的成员属性，指向z1这个属性（是逻辑地址，随对象不同而不同）
    cout << pp->*px << endl;
    px = &Point::z2;
    cout << pp->*px << endl;
    return 0;
}
ENDS(test1)

BEGINS(test2)
using namespace haizei;

int main(){
    Point p(3, 4);
    (p += 5) += 6;
    cout << p << endl;
    cout << "p++ = " << p++ << endl;
    cout << "p = "   << p   << endl;
    cout << "++p = " << ++p << endl;
    
    int n = 45;
    cout << "n = " << (++n)++ << endl; // 47 被加了两次，约定俗成是返回该对象，而不是临时对象

    (++p)++;
    cout << "(++p)++ = " << p << endl;
    return 0;
}
ENDS(test2)


BEGINS(array_object) 
using namespace haizei;
int &Array::operator[](const haizei::Point &a) {
    return data[a.x + a.y];
}
int main(){
    Array arr;
    for (int i = 0; i < 10; i++) {
        arr[i] = i;//返回值得是引用，相关位置变量的引用
    }
    cout << arr["0"] << " " << arr["1"] << endl;
    for (int i = 0; i < 10; i++) {
        cout<<arr[i] << " ";
    }
    cout<<endl;

    const Array arr2;
    for (int i = 0; i < 10; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 10; i++) {
        cout << &arr2[i] << " ";
    }
    cout << endl;
    return 0;
}
ENDS(array_object)

BEGINS(function_object)
class Function {
public:
    int operator()(int a,int b) {
        cout << "inner class : ";
        return a + b;
    }
private:
    
};

int func1(int a, int b) {
    cout << "inner func1 : ";
    return a + b;
}

int main() {
    Function func;
    cout << func(3, 4) << endl; // 本质是一个对象，看起来像函数
    int (*p)(int, int) = func1; // 函数指针
    cout << p(3, 4) << endl; 
    function<int(int, int)> q;
    q = func1;
    cout << "q pointer : " << q(3, 4) << endl;
    q = func;
    cout << "q pointer : " << q(3, 4) << endl;

    cout << greater<int>()(4, 3) << endl; //greater是用来比较第一个数是否大于第二个数的
    cout << greater<int>()(3, 4) << endl;
    //greater<int>是类型，小括号()一写，就是在构造一个临时对象，后面再接一个小括号，里面还有参数，那这个对象不就是一个函数对象么。
    return 0;
}
ENDS(function_object)

BEGINS(pointer_object)
struct A {
    A() : x(0), y(0) {}
    int x, y;
};
ostream &operator<<(ostream &out, const A &a) {
    cout << a.x << " " << a.y;
    return out;
}
class Pointer {
public:
    Pointer(A *p = nullptr) : p(p) {} 
    A *operator->() { return p; }
    A &operator*() { return *p; }
    A *operator+(int n) { return p + n; }
    A *operator-(int n) { return p - n; }
    A &operator[](int n) { return *(p + n); }
    int operator-(const Pointer a) { return p - a.p; }

    A &operator*() const { return *p; }
    A *operator+(int n) const { return p + n; }
    A *operator-(int n) const { return p - n; }
    A &operator[](int n) const { return *(p + n); }
    friend ostream &operator<<(ostream &,const Pointer &);
private:
    A *p;
};
ostream &operator<<(ostream &out, const Pointer &p) {
    cout << p.p;
    return out;
}
int main() {
    A a, b;
    Pointer p = &a, q = &b;//外在表现就像一个指针一样
    cout << a << endl;
    p->x = 3;
    p->y = 4;
    cout << a << endl;
    cout << *p << endl;
    cout << p << endl;
    cout << p + 1 << endl;
    cout << p - 1 << endl;
    cout << p - q << endl; //TODO
    cout << p[0] << endl; //TODO

    const  Pointer cp = &a; //const Pointer指针对象中存储的值不能变
    
    cout << *cp << endl; // TODO
    cout << cp + 1 << endl; //TODO
    cout << cp - 1 << endl; //TODO
    cout << cp[0] << endl;
    
    return 0;
}
ENDS(pointer_object)

int main(){
    // test1::main(); 第一个测试用例
    //test2::main();
    //array_object::main();
    //function_object::main();
    pointer_object::main();
    return 0;
}

