/*************************************************************************
	> File Name: except.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 30 Dec 2022 02:52:44 AM UTC
 ************************************************************************/

#include<iostream>
#include<cstring>
using namespace std;

class MyException : public runtime_error {
public:
    MyException(const string &s) : runtime_error(s) {
        cout << "MyException ctor" << endl;
    }
    const char *what() const noexcept override {
        return "213";
        // noexcept 关键字表示这个函数本身不会再抛出异常了，这是为了防止无线递归的情况。如果还是抛出了异常，主程序会直接结束。
    }
};
int main() {

    try {
        // 可能含有异常的代码
        cout << "throwing" << endl;
        throw (MyException("hello world!"));
        throw ((string)"dsafdavd");
        throw (1);
        cout << "will not excute" << endl; // unreachable code
    } catch (runtime_error &re) {
        cout << re.what() << endl;
    } catch (string &e) {
        cout << "caught an string" << endl;
    } catch (int &e) {
        cout << e << " caught an integer" << endl;
    } catch(...) { //捕获全部异常
        cout << "exception caught" << endl;
    }
    
    cout << "continue from try..." << endl;
    return 0;
}
