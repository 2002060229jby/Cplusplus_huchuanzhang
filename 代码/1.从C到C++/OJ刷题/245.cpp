/*************************************************************************
	> File Name: 245.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Oct 2022 02:24:41 PM UTC
 ************************************************************************/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    int n;
    vector<int> arr;
    cin>>n;
    for (int i = 0, a; i < n; i++) {
        cin >> a;
        arr.push_back(a);
    }
    sort(arr.begin(), arr.end());
    int p = arr[n / 2], sum = 0;
    for (int i = 0; i < n; i++) sum += abs(arr[i] - p);
    cout << sum << endl;
    return 0;
}
