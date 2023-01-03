/*************************************************************************
	> File Name: 8.deep_copy.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 24 Dec 2022 03:30:17 AM UTC
 ************************************************************************/

#include<iostream>
#include<cstring>
using namespace std;
#define BEGINS(x) namespace x {//测试样例
#define ENDS(x) }

BEGINS(haizei)
class A {
public:
    int x, y;
};

ostream &operator<<(ostream &out, const A &a) {
    out << "(" << a.x << ", " << a.y << ") ";
    return out;
}

template<typename T>//引进模板，并把data存储的类型改为任意的T
class Vector{
public:
    Vector(int n = 100) : n(n), data((T *)calloc(sizeof(T), n)) {}
    Vector(const Vector &a) : n(a.n) {
        /*

        // 一、普通做法：简单复制
        data = new T[n]; 
        memcpy(data, a.data, sizeof(T) * n);
        // 这样写究竟有什么问题？答：data里面可能不止存整型那么简单，如果data里的对象也需要深拷贝的时候,比如说指针，那就不适用了。

        // 二、改良做法：原地构造：
        data = new T[n]; 
        for (int i = 0; i < n; i++) {
            new(data + i) T(a.data[i]);
        }
        // 但是程序依然有值得改进的点：
        // 1.如果对象没有默认构造,用new就错了; 
        // 2.对同一片存储空间重复调用了n次构造函数，一开始没必要初始化。
        
        */

        // 三、完美做法：简化构造：
        data = (T *)malloc(sizeof(T) * n);
        for (int i = 0; i < n; i++) {
            new(data + i) T(a.data[i]);
        }
        return ;
    }

    T &at(int ind) { return data[ind]; } // 返回数组ind处的引用

    T &operator[](int ind) { return data[ind]; } // []的重载

    void output(int m = -1) {
        if (data == nullptr) return ;
        if (m == -1) m = n;
        cout << "arr " << this << " : ";
        for (int i = 0; i < m ; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
        return ;
    }
private:
    int n;
    T *data;
};

ENDS(haizei)

BEGINS(test1)

int main() {
    haizei::Vector<int> arr1;
    for (int i = 0; i < 10; i++) arr1[i] = i; // arr.at(i) = i;
    arr1.output(10);
    haizei::Vector<int> arr2(arr1);
    arr2.output(10);
    arr2[3] = 1000;
    arr1.output(10);
    arr2.output(10);
    return 0;
}

ENDS(test1)

BEGINS(test2)

using namespace haizei;
int main() {
    Vector<A> arr1;
    for (int i = 0; i < 10; i++) {
        arr1[i].x = i;
        arr1[i].y = 2 * i;
    }
    arr1.output(10);
    Vector<A> arr2(arr1);
    arr2[3] = (A){4, 1000};
    arr1.output(10);
    arr2.output(10);
    return 0;
}

ENDS(test2)


BEGINS(test3)

using namespace haizei;
int main(){
    Vector<Vector<int>> arr1; //二维数组
    Vector<Vector<int>> arr2(arr1);
    arr2[2][2] = 1000;
    cout << "arr1========" <<endl;
    for (int i = 0; i < 3; i++) { //输出arr1前三行
        arr1[i].output(3);
    }
    cout << "arr2========" <<endl;
    for (int i = 0; i < 3; i++) { //输出arr2前三行
        arr2[i].output(3);
    }
    return 0;
}


ENDS(test3)

int main(){
    cout << "Test1:===========" << endl;
    test1::main(); 
    cout << "Test2:===========" << endl;
    test2::main();
    cout << "Test3:===========" << endl;
    test3::main();
    return 0;
}

