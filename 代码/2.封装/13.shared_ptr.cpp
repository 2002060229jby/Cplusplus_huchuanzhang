/*************************************************************************
	> File Name: 13.shared_ptr.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 28 Dec 2022 07:21:05 AM UTC
 ************************************************************************/

#include<iostream>
#include<memory>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1)
class A {
public:
    A() {
        cout << "default constructor" << endl;
    }  
    ~A() {
        cout << "destructor" << endl;
    }
};

int main() {
    // 原生指针：
    //A *p = new A();
    //delete p; //因为默认析构没了，所以得加上这行才会调用析构。

    // 智能指针：
    shared_ptr<A> p = make_shared<A>(); 
    cout << p.use_count() << endl;
    shared_ptr<A> q = p;
    cout << p.use_count() << endl;
    cout << q.use_count() << endl;
    p = nullptr;
    cout << q.use_count() << endl;
    q = nullptr;
    cout << "end main" << endl;
    
    return 0;
}

ENDS(test1)


BEGINS(test2)
class A {
public:
    A() {
        cout << "default constructor" << endl;
    }  
    ~A() {
        cout << "destructor" << endl;
    }
    shared_ptr<A> p;
};

int main() {
    shared_ptr<A> p = make_shared<A>(); 
    shared_ptr<A> q = make_shared<A>(); 
    p->p = q;
    q->p = p;
    p = nullptr;
    q = nullptr;

    return 0;
}
ENDS(test2)


BEGINS(test3)
class A {
public:
    A(int x = 3, int y = 4) : x(x), y(y) {
        cout << "default constructor" << endl;
    }  
    int x, y;
    ~A() {
        cout << "destructor" << endl;
    }
};
ostream &operator<<(ostream &out, const A &a) {
    out << "class A : "<< a.x << "," << a.y;
    return out;
}
class ptr_data {
public:
    ptr_data(A *ptr, int *cnt = nullptr) : 
    ptr(ptr), cnt(cnt) {
        if (cnt == nullptr) this->cnt = new int(1);
    }
    void increase_one() {
        *cnt += 1;
        return ;
    }
    void decrease_one() {
        *cnt -= 1;
        if (*cnt == 0) delete ptr;
        return ;
    }
    bool operator==(const ptr_data &p) const {
        return ptr == p.ptr && cnt == p.cnt;
    }

    A *ptr;
    int *cnt;// 存储一个引用计数指针
};

class shared_ptr {
public:
    shared_ptr(A *ptr) : p(ptr) {}
    shared_ptr(const shared_ptr &p) : p(p.p) {
        this->p.increase_one();
    }
    shared_ptr &operator=(const shared_ptr &obj) {
        if (obj.p == p) return *this;//判断是否指向同一对象
        p.decrease_one();
        p = obj.p;
        p.increase_one();
    }
    A *operator->() { return p.ptr; }
    A &operator*() { return *(p.ptr); }
    int use_count() { return *p.cnt; }
    ~shared_ptr() {
        p.decrease_one();
    }
private:
    ptr_data p;
};
shared_ptr make_shared() {
    return shared_ptr(new A());
}
int main() {
    shared_ptr p = make_shared(); //RVO返回值优化 
    p->x = 3, p->y = 4;
    cout << *p << endl;
    cout << p.use_count() << endl;
    shared_ptr q = p;
    cout << p.use_count() << endl;
    cout << q.use_count() << endl;
    p = nullptr;
    cout << q.use_count() << endl;
    q = nullptr;
    return 0;
}

ENDS(test3)


int main() { 
    // test1::main();
    // test2::main();
    test3::main();
    return 0;
}
