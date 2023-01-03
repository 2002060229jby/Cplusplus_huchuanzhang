/*************************************************************************
	> File Name: 4.constructor.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Oct 2022 02:17:47 AM UTC
 ************************************************************************/

#include<iostream>
using namespace std;
void add_one(int &n) {
    n += 1;
    return ;
}

int main(){
    int a = 1, b = 3;
    cout << "normal param : " << a << " " << b << endl;
    add_one(a);
    add_one(b);
    cout << a << " " << b << endl;

    return 0;
}
