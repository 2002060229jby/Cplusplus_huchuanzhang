/*************************************************************************
	> File Name: 11.reload.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 25 Dec 2022 05:41:50 AM UTC
 ************************************************************************/

#include<iostream>
#include<cmath>
#include<cstring>
using namespace std;

int func(int x) {
    return 2 * x;
}

int ABS(int x) {
    return abs(x);
}
double ABS(double x) {
    return fabs(x);
}
// 实现扩展已有功能

int func(double x) {
    return x + 1000; 
}

void output_permutation(int ind, int n, int *num, int *buff) {
    //ind表示存到第几位了
    if(ind == n) {
        for (int i = 0; i < n; i++) {
            cout << buff[i];
        }
        cout << endl;
    }
    for (int i = 1; i <= n; i++) {
        if (num[i]) continue;
        buff[ind] = i;
        num[i] = 1;
        output_permutation(ind + 1, n, num, buff);
        num[i] = 0;
    }
    return ;
}
void output_permutation(int n) {
    int num[n + 1], buff[n]; // num记录数是否被用过,buff用来暂存数。
    memset(num,  0, sizeof(num));
    memset(buff, 0, sizeof(buff));
    output_permutation(0, n, num, buff);
    return ;
}

int main() {
    cout << func(2) << endl;
    cout << func(2.0) << endl;
    cout << ABS(-2) << endl;
    cout << ABS(-2.3) << endl;
    output_permutation(4);
    return 0;
}
