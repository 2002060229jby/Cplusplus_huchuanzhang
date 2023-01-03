/*************************************************************************
	> File Name: 287.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Oct 2022 03:03:33 PM UTC
 ************************************************************************/

#include<iostream>
#include<set>
using namespace std;

typedef pair<int, int> PII;

int main() {
    set<PII> s;
    int n, t = 0;
    cin >> n;
    for (int i = 0, a; i < n; i++) {
        cin >> a;
        s.insert(PII(a, t++));
    }
    int sum = 0;
    for (int i = 1; i < n; i++) {
        int a = s.begin()->first; s.erase(s.begin());
        int b = s.begin()->first; s.erase(s.begin());
        sum += a + b;
        s.insert(PII(a + b, t++));
    }
    cout << sum << endl;
    return 0;
}
