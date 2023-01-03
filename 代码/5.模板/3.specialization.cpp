/*************************************************************************
	> File Name: 3.specialization.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 31 Dec 2022 08:32:16 AM UTC
 ************************************************************************/

#include<iostream>
using namespace std;
#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1)
template<typename T>
T add(T a, T b) {
    return a + b;
}
// 在输出整型的时候额外输出一段信息（用到全特化）
template<>
int add<int>(int a, int b) {
    cout << "int template " << endl;
    return a + b;
}
int main() {
    cout << add(3, 4) << endl;
    cout << add(3.1, 4.2) << endl;
    return 0;
}
ENDS(test1)

BEGINS(test2)
template<typename T, typename u>
class Test {
public:
    Test() {
        cout << "normal template<T, U>" << endl;
    }
};
template<>
class Test<int, double> {
public:
    Test() {
        cout << "specialization template<int, double>" << endl;
    }
};
template<typename T>
class Test<int, T> {
public:
    Test() {
        cout << "partial specialization template<int, T>" << endl;
    }
};
int main() {
    Test<string, int> t1; // 正常的
    Test<int, double> t2; // 全特化,比偏特化优先级高
    Test<int, string> t3; // 偏特化
    return 0;
}
ENDS(test2)

BEGINS(test3)
class A {};
class B {};

class yes_constructor {
public:
    static const char *has_constructor;
};
const char *yes_constructor::has_constructor = "yes";

class no_constructor{
public:
    static const char *has_constructor;
};
const char *no_constructor::has_constructor = "no";


template<typename T>
class type_trais : public yes_constructor {};

// 对所有的指针,没有构造函数,输出no
template<typename T>
class type_trais<T *> : public no_constructor {};

template<>
class type_trais<int> : public no_constructor {};

template<>
class type_trais<double> : public no_constructor {};

#define TEST(type) \
    cout << #type << " : " << type_trais<type>::has_constructor << endl;

int main() {
    TEST(int);
    TEST(A);
    TEST(double);
    TEST(B);
    TEST(string);
    TEST(string *);
    return 0;
}
#undef TEST
ENDS(test3)

BEGINS(test4)
class A {};
class B {};

class yes_constructor {};
class no_constructor{};

template<typename T>
class type_trais {
public:
    typedef yes_constructor has_constructor;
};

// 对所有的指针,没有构造函数,输出no
template<typename T>
class type_trais<T *> {
public:
    typedef no_constructor has_constructor;
};

template<>
class type_trais<int> {
public:
    typedef no_constructor has_constructor;
};

template<>
class type_trais<double> {
public:
    typedef no_constructor has_constructor;
};

ostream &operator<<(ostream &out, const yes_constructor &) {
    out << "yes";
    return out;
}
ostream &operator<<(ostream &out, const no_constructor &) {
    out << "no";
    return out;
}
#define TEST(type) \
    cout << #type << " : " << type_trais<type>::has_constructor() << endl;
int main() {
    TEST(int);
    TEST(A);
    TEST(double);
    TEST(B);
    TEST(string);
    TEST(string *);
    return 0;
}
#undef TEST
ENDS(test4)

int main() {
    // test1::main();
    // test2::main();
    // test3::main();
    test4::main();
    return 0;
}
