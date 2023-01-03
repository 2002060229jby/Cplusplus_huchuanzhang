/*************************************************************************
	> File Name: 3.set.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Oct 2022 02:59:19 PM UTC
 ************************************************************************/

#include<iostream>
#include<set>
using namespace std;
int main() {
    set<int> s;
    s.insert(3);
    s.insert(6);
    s.insert(-12);
    s.insert(9);
    s.insert(5);
    s.insert(3);
    s.insert(3);
    for (auto iter = s.begin(); iter != s.end(); iter++) {
        cout << *iter <<endl;
    }
    s.erase(s.begin());//小顶堆
    return 0;
}
