/*************************************************************************
	> File Name: 3.cout.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Oct 2022 01:26:47 AM UTC
 ************************************************************************/

#include<iostream>
#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(haizei)
class istream {
public:
    istream &operator>>(int &x);
};
class ostream {
public:
    ostream &operator<<(int x);
    ostream &operator<<(char ch);
};
istream &istream::operator>>(int &x) {
    scanf("%d", &x);
    return *this;
}
ostream &ostream::operator<<(int x) {
    printf("%d", x);
    return *this;
}
ostream &ostream::operator<<(char x) {
    printf("%c", x);
    return *this;
}
ostream cout;
istream cin;
const char endl = '\n';
ENDS(haizei)

int main() {
    int n, m;
    std::cin >> n >> m;
    std::cout << n << m << std::endl;
    haizei::cin >> n >> m;
    haizei::cout << n << m << haizei::endl;
    return 0;
}
