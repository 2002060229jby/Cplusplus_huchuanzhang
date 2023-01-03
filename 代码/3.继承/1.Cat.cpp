/*************************************************************************
	> File Name: 1.Cat.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 29 Dec 2022 03:30:12 AM UTC
 ************************************************************************/

#include<iostream>
using namespace std;
#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1)
class Base {
public:
    int x;
protected:
    int y;
private:
    int z;
};
class public_Base : public Base {
public:
    void main() {
        x = 2; // ok, x public
        y = 3; // ok, y protected
        // z = 4; // no, z private
    }
};
class protected_Base : protected Base {
public:
    void main() {
        x = 2;
        y = 3;
        // z = 4; // no, private
    }
};
class private_Base : private Base {
public:
    void main() {
        x = 2;
        y = 3;
        // z = 4; // no, private
    }
};
int main() {
    public_Base a;
    a.x = 3;
    // a.y = 4; // no, protected外界无法访问。
    // a.z = 5; // no, private

    protected_Base b;
    // b.x = 3; // no, protected + public = protected
    // a.y = 4; // no, protected + protected
    // a.z = 5; // no, private


    private_Base c;
    // c.x = 3; // no, private + public = private
    // c.y = 4; // no, private + protected
    // c.z = 5; // no, private
    return 0;
}
ENDS(test1)


BEGINS(test2) 
class Base {
public:
    Base(string name) : class_name(name) {}
    int x;
    string class_name;
private:
    int y;
};
class A : public Base {
public:
    A() : Base("class_A") {}
};
class B : public Base {
public:
    B() : Base("class_B") {}
};
class C : public Base {
public:
    C() : Base("class_C") {}
};
void func(Base &b) {
    cout << "input class : " << b.class_name << endl;
}
int main() {
    A a;
    B b;
    C c;
    func(a);
    func(b);
    func(c); // 隐式类型转换
    cout << "sizeof(Base) = " << sizeof(Base) << endl;
    cout << "sizeof(A) = " << sizeof(A) << endl;

    return 0;
}
ENDS(test2)


BEGINS(test3) 
class Base {
public:
    Base(string name) : class_name(name) {}
    int x;
    string class_name;
private:
    int y;
};
class A : public Base {
public:
    A() : Base("class_A") {}
};
class B : public Base {
public:
    B() : Base("class_B") {}
};
class C : public Base {
public:
    C() : Base("class_C") {}
};
void func(Base *b) {
    cout << "input class : " << b->class_name << endl;
}
int main() {
    A a;
    B b;
    C c;
    func(&a);
    func(&b);
    func(&c); // 隐式类型转换
    cout << "sizeof(Base) = " << sizeof(Base) << endl;
    cout << "sizeof(A) = " << sizeof(A) << endl;

    return 0;
}
ENDS(test3)

BEGINS(test4)
class ATTR_BASE {
public:
    ATTR_BASE(string name) : name(name) {
        cout << "constructor : " << name << endl;
    }
    ~ATTR_BASE() {
        cout << "destructor : " << name << endl;
    }
    string name;
};

class ATTR1 : public ATTR_BASE {
public:
    ATTR1(string name) : ATTR_BASE(name) {}
};

class ATTR2 : public ATTR_BASE {
public:
    ATTR2(string name) : ATTR_BASE(name) {}
};

class Base {
public:
    Base() : attr1("attr1 in Base"), attr2("attr2 in Base") {
        cout << "Base constructor done" << endl;
    }
    ~Base() {
        cout << "Base destructor done" << endl;
    }
private:
    ATTR1 attr1;
    ATTR2 attr2;
};

class A : public Base {
public:
    A() : Base(), attr1("attr1 in A"), attr2("attr2 in A") {
        cout << "A constructor done" << endl;
    }
    ~A() {
        cout << "A destructor done" << endl;
    }
private:
    ATTR1 attr1;
    ATTR2 attr2;
};

int main() {
    A a;

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
