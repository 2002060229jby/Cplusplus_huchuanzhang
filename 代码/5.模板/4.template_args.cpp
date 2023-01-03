/*************************************************************************
	> File Name: 4.template_args.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 31 Dec 2022 11:09:26 AM UTC
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x{
#define ENDS(x) }

BEGINS(test1)
// 可以打印任意个参数
class A {
public:
    A(int x, int y) : x(x), y(y) {}
    int x, y;
};
ostream &operator<<(ostream &out, const A &a) {
    out << "Class A : " << a.x << " " << a.y;
    return out;
}

template<typename T> 
void Print(T a) {
    cout << a << endl;
    return ;
}
// 这不是模板函数的偏特化，偏特化是可以放在下面的，
// 而且模板函数没有偏特化版本
template<typename T, typename ...ARGS>
void Print(T a, ARGS... args) {
    cout << a << " | ";
    Print(args...);//没有递归终止条件怎么办？——给出终止模板
    return ;
}

int main() {
    A a(5, 6);
    Print("hello world");
    Print("hello world", 3, 3.4, a);
    Print(3, a, 6.7, "hello world");
    return 0;
}
ENDS(test1)

BEGINS(test2)

template<typename T, typename ...ARGS>
class ARG {
public:
    typedef T type;
    typedef ARG<ARGS...> rest;
};
template<typename T>
class ARG<T> {
public:
    typedef T type;
};

template<typename T, typename ...ARGS>
class Test {
public:
    T operator()(typename ARG<ARGS...>::type a, typename ARG<ARGS...>::rest::type b) {
        return a + b;
    }
};

int main() {
    Test<int, int, int> t1;
    Test<double, double, int> t2;
    cout << t1(3, 4) << endl;
    cout << t2(3.5, 4) << endl;
    return 0;
}
ENDS(test2)


BEGINS(test3)
template<typename T, typename ...ARGS>
class ARG {
public:
    typedef T type;
    typedef ARG<ARGS...> rest;
};
template<typename T>
class ARG<T> {
public:
    typedef T type;
    typedef T ftype;//只有最后一层能接触到ftype，跟传的参数个数有影响
};

template<typename T, typename ...ARGS>
class Test {
public:
    T operator()(
        typename ARG<ARGS...>::type a, 
        typename ARG<ARGS...>::rest::ftype b) {
        return a + b;
    }
};

int main() {
    Test<int, int, int> t1;
    Test<double, double, int> t2;
    // Test<double, int, int, int> t3;
    cout << t1(3, 4) << endl;
    cout << t2(3.5, 4) << endl;
    return 0;
}
ENDS(test3)

BEGINS(test4)
template<typename T, typename ...ARGS>
class ARG {
public:
    typedef T type;
    typedef ARG<ARGS...> rest;
};
template<typename T>
class ARG<T> {
public:
    typedef T type;
    typedef T ftype;//只有最后一层能接触到ftype，跟传的参数个数有影响
};

template<typename T, typename ...ARGS> class Test;// 原模板声明
template<typename T, typename ...ARGS>
class Test<T(ARGS...)> {
public:
    T operator()(
        typename ARG<ARGS...>::type a, 
        typename ARG<ARGS...>::rest::ftype b) {
        return a + b;
    }
};

int main() {
    Test<int(int, int)> t1;
    Test<double(double, int)> t2;
    // Test<double, int, int, int> t3;
    cout << t1(3, 4) << endl;
    cout << t2(3.5, 4) << endl;
    return 0;
}
ENDS(test4)

BEGINS(test5)

template<int M>
void Print() {
    cout << M << ", ";
    Print<M - 1>();
    return ;
}
template<>
void Print<1>() {
    cout << 1 << endl;
    return ; 
}
int main() {
    Print<10>();
    Print<5>();
    Print<6>();
    Print<7>();
    return 0;
}
ENDS(test5)

BEGINS(test6)
template<int N, typename T, typename ...ARGS>
struct ARG {
    typedef typename ARG<N-1, ARGS...>::type type;
};
template<typename T, typename ...ARGS>
struct ARG<1, T, ARGS...> {
    typedef T type;
};
template<typename T>
struct ARG<1, T> {
    typedef T type;
};

// 首先需要几个东西：
// 1. 统计变参列表中参数个数的模板
template<typename T, typename ...ARGS>
struct NUM_ARGS {
	// 应该有一个编译器常量用来计数：
	static constexpr int r = NUM_ARGS<ARGS...>::r + 1; 
};
// 偏特化版本，定义递归边界
template<typename T>
struct NUM_ARGS<T> {
	static constexpr int r = 1;
};

template<int N>
struct Zero {
    typedef int no;
};
template<>
struct Zero<0> {
    typedef int yes;
};

template<typename T, typename ...ARGS> class Test;
template<typename T, typename ...ARGS> 
class Test<T(ARGS...)> {
public:
    typedef typename Zero<2 - NUM_ARGS<ARGS...>::r>::yes TYPE_NUM_2;
    // typedef ARG<2, ARGS...>::ftype TYPE_NUM_2;
    T operator()(
        typename ARG<1, ARGS...>::type a, 
        typename ARG<2, ARGS...>::type b) {
        return a + b;
    }
};

int main() {
    cout << NUM_ARGS<int, int, int, int>::r << endl;
	cout << NUM_ARGS<int, int, int>::r << endl;
	cout << NUM_ARGS<int, int>::r << endl;
    Test<bool(int, int)> t1;
    // Test<bool(int, int, int)> t2;
    cout << t1(3, 4) << endl;

    return 0;
}
ENDS(test6)

int main() {
    // test1::main();
    // test2::main();
    // test3::main();
    // test4::main();
    // test5::main();
	test6::main();
    return 0;
}
