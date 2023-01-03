/*************************************************************************
	> File Name: 14.sort.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 28 Dec 2022 12:19:40 PM UTC
 ************************************************************************/

#include<iostream>
#include<algorithm>
#include<functional>
using namespace std;
#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(test1)
bool cmp1(int a, int b) {
    return a > b;
}
void output(int *first, int *last, const char *msg) {
    cout << msg;
    while (first != last) {
        cout << *first << " ";
        ++first;
    }
    cout << endl;
    return ;
}
class CMP {
public:
    bool operator()(int a, int b) {
        return a < b;
    }
};
int main() {
    int arr[100], n;
    cin >> n;
    for (int i = 0; i < n; i ++) cin >> arr[i];
    sort(arr, arr + n);
    output(arr, arr + n, "none : ");

    sort(arr, arr + n, cmp1);//普通函数
    output(arr, arr + n, "cmp1 : ");

    CMP cmp2;//函数对象
    sort(arr, arr + n, cmp2);
    output(arr, arr + n, "cmp2 : ");
    return 0;
}
ENDS(test1)


BEGINS(test2)
bool cmp1(int a, int b) {
    return a > b;
}
void output(int *first, int *last, const char *msg) {
    cout << msg;
    while (first != last) {
        cout << *first << " ";
        ++first;
    }
    cout << endl;
    return ;
}
class CMP {
public:
    bool operator()(int a, int b) {
        return a < b;
    }
};
//普通版实现
/*
void sort(int *first, int *last, function<bool(int, int)> cmp = less<int>()) {
    if (first >= last) return ;
    int *x = first, *y = last - 1, z = *first;
    while (x < y) {
        while (x < y && cmp(z, *y)) --y;
        if (x < y) *(x++) = *y;
        while (x < y && cmp(*x, z)) ++x;
        if (x < y) *(y--) = *x;
    }
    *x = z;
    sort(first, x, cmp);
    sort(x + 1, last, cmp);
    return ;
}
*/
const int threshold = 16;

void intro_loop(int *first, int *last, function<bool(int, int)> cmp = less<int>()) {
    while (last - first > threshold) {
        int *x = first, *y = last - 1, z = *first;
        do {
            while (cmp(*x, z)) ++x;
            while (cmp(z, *y)) --y;
            if (x <= y) {
                swap(*x, *y);
                ++x; --y;
            }
        } while (x <= y);
        intro_loop(x, last, cmp);
        last = y + 1;
        return ;
    }
}
void insertion_sort(int *first, int *last, function<bool(int, int)>cmp = less<int>()) {
    int *ind = first;
    for (int *x = first + 1; x < last; ++x) {
        if (cmp(*x, *ind)) ind = x;
    }
    while (ind != first) {
        swap(*ind, *(ind - 1));
        --ind;
    }
    for (int *x = first + 2; x < last; ++x) {
        int *j = x;
        while (cmp(*j, *(j - 1))) {
            swap(*j, *(j - 1));
            --j;
        }
    }
    return ;
}
void sort(int *first, int *last, function<bool(int, int)>cmp = less<int>()) {
    intro_loop(first, last, cmp);
    insertion_sort(first, last, cmp);
    return ;
}
int main() {
    int arr[100], n;
    cin >> n;
    for (int i = 0; i < n; i ++) cin >> arr[i];
    sort(arr, arr + n);
    output(arr, arr + n, "none : ");

    sort(arr, arr + n, cmp1);//普通函数
    output(arr, arr + n, "cmp1 : ");

    CMP cmp2;//函数对象
    sort(arr, arr + n, cmp2);
    output(arr, arr + n, "cmp2 : ");
    return 0;
}
ENDS(test2)


BEGINS(test3)
bool cmp1(int a, int b) {
    return a > b;
}
void output(int *first, int *last, const char *msg) {
    cout << msg;
    while (first != last) {
        cout << *first << " ";
        ++first;
    }
    cout << endl;
    return ;
}
class CMP {
public:
    bool operator()(int a, int b) {
        return a < b;
    }
};
const int threshold = 16;
class RandomIter {
public:
    RandomIter(int *a) : ptr(a) {}
    int operator-(const RandomIter &a) { return ptr-a.ptr; } 
    RandomIter operator-(int n) { return RandomIter(ptr - n); } 
    RandomIter operator+(int n) { return RandomIter(ptr + n); } 
    int &operator*() { return *ptr; } 
    RandomIter &operator++() { ++ptr; return *this; }
    RandomIter &operator--() { --ptr; return *this; }
    bool operator<(const RandomIter &a) const { return ptr < a.ptr; }
    bool operator>(const RandomIter &a) const { return a < *this; }
    bool operator<=(const RandomIter &a) const { return !(a < *this); }
    bool operator>=(const RandomIter &a) const { return !(*this < a); }
    bool operator==(const RandomIter &a) { return !(*this < a) && !(a < *this); }
    bool operator!=(const RandomIter &a) { return !(*this == a); }

private:
    int *ptr;
};

void intro_loop(RandomIter first, RandomIter last, function<bool(int, int)> cmp = less<int>()) {
    while (last - first > threshold) {
        RandomIter x = first, y = last - 1;
        int z = *first;
        do {
            while (cmp(*x, z)) ++x;
            while (cmp(z, *y)) --y;
            if (x <= y) {
                swap(*x, *y);
                ++x; --y;
            }
        } while (x <= y);
        intro_loop(x, last, cmp);
        last = y + 1;
        return ;
    }
}
void insertion_sort(RandomIter first, RandomIter last, function<bool(int, int)>cmp = less<int>()) {
    RandomIter ind = first;
    for (RandomIter x = first + 1; x < last; ++x) {
        if (cmp(*x, *ind)) ind = x;
    }
    while (ind != first) {
        swap(*ind, *(ind - 1));
        --ind;
    }
    for (RandomIter x = first + 2; x < last; ++x) {
        RandomIter j = x;
        while (cmp(*j, *(j - 1))) {
            swap(*j, *(j - 1));
            --j;
        }
    }
    return ;
}
void sort(RandomIter first, RandomIter last, function<bool(int, int)>cmp = less<int>()) {
    intro_loop(first, last, cmp);
    insertion_sort(first, last, cmp);
    return ;
}
int main() {
    int arr[100], n;
    cin >> n;
    for (int i = 0; i < n; i ++) cin >> arr[i];
    sort(arr, arr + n);
    output(arr, arr + n, "none : ");

    sort(arr, arr + n, cmp1);//普通函数
    output(arr, arr + n, "cmp1 : ");

    CMP cmp2;//函数对象
    sort(arr, arr + n, cmp2);
    output(arr, arr + n, "cmp2 : ");
    return 0;
}
ENDS(test3)

int main() {
    // test1::main();
    // test2::main();
    test3::main();
    return 0;
}
