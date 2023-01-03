/*************************************************************************
	> File Name: 1.class.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Oct 2022 01:18:49 PM UTC
 ************************************************************************/

#include<iostream>

namespace haizei {
    int a, b;
}
namespace haizei {
    int c, d;
}

using namespace haizei;

int main(){
    haizei::a = haizei::b = haizei::c = haizei::d = 1;
    std::cout << haizei::a << std::endl;
    a = b = c = d = 2;
    std::cout << a << std::endl;

    return 0;
}
