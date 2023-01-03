/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 28 Dec 2022 05:25:06 AM UTC
 ************************************************************************/

#include<iostream>
using namespace std;
class Array {
public:
    Array(int n = 100) : n(n), data(new int[n]) {}


private:
    int n;
    int *data;
};

int main() {
    Array arr(10);


    return 0;
}
