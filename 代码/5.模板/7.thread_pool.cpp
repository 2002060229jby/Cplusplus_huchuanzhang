/*************************************************************************
	> File Name: 7.thread_pool.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 02 Jan 2023 05:06:24 AM UTC
 ************************************************************************/

#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
#include<thread>
#include<mutex>
#include<functional>
#include<condition_variable>
using namespace std;
#define BEGINS(x) namespace x {
#define ENDS(x) }

BEGINS(thread_usage)
void func() {
    cout << "hello world" << endl;
    return ;
}
void print(int a, int b) {
    cout << a << " " << b << endl;
    return ;
}

int main() {
    thread t1(func);//t1已经开始运行了
    t1.join(); // 等待t1线程结束
    thread t2(print, 3, 4);
    t2.join(); 
    return 0;
}
ENDS(thread_usage)

BEGINS(prime_count_test)
bool is_prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}
// 多线程功能函数：
int prime_count(int l, int r) {
    // 从l到r范围内素数的数量
    int ans = 0;
    for (int i = l; i <= r; i++) {
        ans += is_prime(i);
    }
    return ans;
}
// 多线程入口函数：
void worker(int l, int r, int &ret) {
    cout << this_thread::get_id() << "begin" << endl;
    ret = prime_count(l, r);
    cout << this_thread::get_id() << "done" << endl;
    return ;
}
int main() {
    #define batch 1000000
    thread *t[10];
    int ret[10];
    // 开辟十个线程：
    for (int i = 0, j = 1; i < 10; i++, j += batch) {
        t[i] = new thread(worker, j, j + batch - 1, ref(ret[i]));
    }
    for (auto x : t) x->join();
    int ans = 0;
    for (auto x : ret) ans += x;
    for (auto x : t) delete x;
    cout << ans << endl;
    return 0;
    #undef batch
}
ENDS(prime_count_test)


BEGINS(prime_count_test1)
int ans = 0;
std::mutex m_mutex;

bool is_prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}
// 多线程功能函数：
void prime_count(int l, int r) {
    cout << this_thread::get_id() << "begin" << endl;
    // 从l到r范围内素数的数量
    for (int i = l; i <= r; i++) {
        unique_lock<mutex> lock(m_mutex); // 临界区
        ans += is_prime(i); // ans为临界资源
        lock.unlock();
    }
    cout << this_thread::get_id() << "done" << endl;
    return ;
}
int main() {
    #define batch 1000000
    thread *t[10];
    // 开辟十个线程：
    for (int i = 0, j = 1; i < 10; i++, j += batch) {
        t[i] = new thread(prime_count, j, j + batch - 1);
    }
    for (auto x : t) x->join();
    for (auto x : t) delete x;
    cout << ans << endl;
    return 0;
    #undef batch
}
ENDS(prime_count_test1)


BEGINS(prime_count_test2)
int ans = 0;
std::mutex m_mutex;

bool is_prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}
// 多线程功能函数：
void prime_count(int l, int r) {
    cout << this_thread::get_id() << "begin" << endl;
    // 从l到r范围内素数的数量
    for (int i = l; i <= r; i++) {
        int ret = is_prime(i);
        __sync_fetch_and_add(&ans, ret);
    }
    cout << this_thread::get_id() << "done" << endl;
    return ;
}
int main() {
    #define batch 1000000
    thread *t[10];
    // 开辟十个线程：
    for (int i = 0, j = 1; i < 10; i++, j += batch) {
        t[i] = new thread(prime_count, j, j + batch - 1);
    }
    for (auto x : t) x->join();
    for (auto x : t) delete x;
    cout << ans << endl;
    return 0;
    #undef batch
}
ENDS(prime_count_test2)

BEGINS(task_test)
class Task {
public:
    template<typename FUNC_T, typename ...ARGS>
    Task(FUNC_T func, ARGS ...args) {
        // 一定要用参数的原有类型进行向下传递。
        this->func = bind(func, forward<ARGS>(args)...);
    }
    void run() {
        func();
        return ;
    }
private:
    function<void()> func;
};
void func(int a, int b) {
    cout << "function " << a << " " << b << endl;
    return ;
}
void test() {
    cout << "hello world : function test" << endl;
    return ;
}
void add_one(int &n) {
    n += 1;
    return ;
}
int main() {
    Task t1(func, 3, 4);
    t1.run();
    t1.run();
    Task t2(test);
    t2.run();
    int n = 1;
    cout << "origin : " <<n << endl;
    Task t3(add_one, ref(n)); // 模板会默认把n识别为int而不是int &
    t3.run();
    cout << "after one added : " << n << endl;
    return 0;
}
ENDS(task_test)

BEGINS(thread_pool_test)
class Task {
public:
    template<typename FUNC_T, typename ...ARGS>
    Task(FUNC_T func, ARGS ...args) {
        // 一定要用参数的原有类型进行向下传递。
        this->func = bind(func, forward<ARGS>(args)...);
    }
    void run() {
        func();
        return ;
    }
private:
    function<void()> func;
};
class ThreadPool {
public:
    ThreadPool(int n = 1) : thread_size(n), threads(n), starting(false) {
        this->start();
        return ;
    }
    void worker() {
        auto id = this_thread::get_id();
        running[id] = true;
        while (running[id]) {
            // 取任务
            Task *t = get_task(); //只是内部的实现方法
            // 执行任务
            t->run();
            delete t;
        }
        return ;
    }
    template<typename FUNC_T, typename ...ARGS>
    void add_task(FUNC_T func, ARGS ...args) {
        unique_lock<mutex> lock(m_mutex);// 访问临界资源
        tasks.push(new Task(func, forward<ARGS>(args)...));
        m_cond.notify_one();// 通知所有等待这个条件信号的线程
        return ;
    }
    void start() {
        if (starting == true) return ;
        for (int i = 0; i < thread_size; i++) {
            threads[i] = new thread(&ThreadPool::worker, this);
        }
        starting = true;
        return ;
    }
    void stop() {
        if (starting == false) return ;
        // 毒药任务，添加到任务队列末尾。
        for (int i = 0; i < threads.size(); i++) {
            this->add_task(&ThreadPool::stop_running, this);
        }
        for (int i = 0; i < threads.size(); i++) {
            threads[i]->join();
        }
        for (int i = 0; i < threads.size(); i++) {
            delete threads[i];
            threads[i] = nullptr;
        }
        starting = false;
        return ;
    }
    ~ThreadPool() {
        this->stop();
        while (!tasks.empty()) {
            delete tasks.front();
            tasks.pop();
        }
        return ;
    }
private:
    bool starting;
    int thread_size;
    Task *get_task() {
        unique_lock<mutex> lock(m_mutex);
        while (tasks.empty()) m_cond.wait(lock);
        Task *t = tasks.front();
        tasks.pop();
        return t;
    }
    std::mutex m_mutex;
    condition_variable m_cond;
    void stop_running() {
        auto id = this_thread::get_id();
        running[id] = false;
        return ;
    }
    vector<thread *> threads;
    unordered_map<decltype(this_thread::get_id()), bool> running;
    queue<Task *> tasks;//存放每一个任务对象的地址
};
bool is_prime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}
// 多线程功能函数：
int prime_count(int l, int r) {
    // 从l到r范围内素数的数量
    int ans = 0;
    for (int i = l; i <= r; i++) {
        ans += is_prime(i);
    }
    return ans;
}
// 多线程入口函数：
void worker(int l, int r, int &ret) {
    cout << this_thread::get_id() << "begin" << endl;
    ret = prime_count(l, r);
    cout << this_thread::get_id() << "done" << endl;
    return ;
}
int main() {
    #define batch 500000
    ThreadPool tp(5);
    int ret[10];
    for (int i = 0, j = 1; i < 10; i++, j += batch) {
        tp.add_task(worker, j, j + batch - 1, ref(ret[i]));
    } 
    tp.stop(); //等待所有任务的结束。
    int ans = 0;
    for (auto x : ret) ans += x;
    cout << ans << endl;
    return 0;
}
ENDS(thread_pool_test)

int main() {
    // thread_usage::main();
    // prime_count_test::main();
    // prime_count_test1::main();
    // prime_count_test2::main();
    // task_test::main();
    thread_pool_test::main();

    return 0;
}
