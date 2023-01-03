/*************************************************************************
	> File Name: 2.class.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Oct 2022 01:24:08 PM UTC
 ************************************************************************/

#include<iostream>
using namespace std;

#define BEGINS(x) namespace x {
#define ENDS(x) } // end of namespace x

BEGINS(haizei)

class A_with_int {
    int a;
    double b;
    void say();
};
void A_with_int::say() {
    cout << "hello world" << endl;
}

class People {
public:
    string name;
    int age;
    double height;
    double weight;

    void say(string name);  
    void run();
};

ENDS(haizei)

void haizei::People::say(string name) { 
    cout << "my first name is " << this->name << endl;
    cout << "my second name is " << name << endl;
}

int main() {
    cout << sizeof(haizei::A_with_int) <<endl;
    haizei::People hug;
    haizei::People zhangpei;
    haizei::People hanmingtao;
    haizei::People zhangxueqi;
    hug.name = "Captain Hu";
    zhangpei.name = "Doctor Zhang";
    hanmingtao.name = "Boss Han";
    zhangxueqi.name = "Leader Zhang";
    hug.say("Xiao Hu");
    zhangpei.say("Xiao Zhang");
    hanmingtao.say("Xiao Han");
    zhangxueqi.say("Xiao Zhang");

    return 0;
}
