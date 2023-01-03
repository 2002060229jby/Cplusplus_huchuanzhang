/*************************************************************************
	> File Name: 166.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Oct 2022 02:44:56 PM UTC
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;
int main() {
    string a, b;
    int pos;
    cin >> a >> pos >> b;
    cout << min(100, (int)a.size()) << endl;
    a.insert(pos - 1, b);
    cout << a << endl;
    cout << a.size() - a.rfind("x") << endl;
    return 0;
}
