/*************************************************************************
	> File Name: 4.priority_queue.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 30 Dec 2022 06:12:08 AM UTC
 ************************************************************************/

#include<iostream>
#include<functional>
using namespace std;
namespace haizei{


//队列的接口类
class IQueue {
public:
    virtual void push(int) = 0;
    virtual void pop() = 0;
    virtual bool empty() const = 0;
    virtual int top() const = 0;
    virtual int front() const = 0;
    virtual int size() const = 0;
    virtual ~IQueue() {};
};

class queue : public IQueue {
private:
    friend ostream &operator<<(ostream &, const queue &);
    int *data;
    int head, tail, count, __size;
    void expand() {
        queue q(2 * __size);
        while (!empty()) {
            q.push(front());
            pop();
        }
        this->swap(q);
        return ;
    }
    int top() const override { return data[head]; }
public: 
    queue(int n = 10) : data(new int[n]), head(0), tail(0), count(0), __size(n) {}
    void push(int val) override {
        if (count == __size) {
            expand();
        }
        data[tail++] = val;
        tail %= __size;
        count += 1;
        return ;
    }
    void pop() override { 
        if (empty()) return ;
        head += 1;
        head %= __size;
        count -= 1;
        return ;
    }
    bool empty() const override { return count == 0; }
    int front()  const override { return data[head];  }
    int size()   const override { return count; }
    void swap(queue &q) {
        std::swap(this->data, q.data);
        std::swap(this->head, q.head);
        std::swap(this->tail, q.tail);
        std::swap(this->count, q.count);
        std::swap(this->__size, q.__size);
        return ;
    }
    ~queue() {
        if (data) delete[] data;
        return ;
    }
};
//优先队列：弹出最大值
class priority_queue : public IQueue {
private:
    friend ostream &operator<<(ostream &, const priority_queue &);
    typedef function<bool(int, int)> CMP_T;
    int *raw_data, *data;
    int count, __size;
    CMP_T cmp;
    void expand() {
        priority_queue q(cmp, 2 * __size);
        while (!empty()) {
            q.push(front());
            pop();
        }
        this->swap(q);
        return ;
    }
    void up_maintain(int ind) {
        if (ind == 1) return ;
        if (cmp(data[ind >> 1], data[ind])) {
            std::swap(data[ind], data[ind >> 1]);
            up_maintain(ind >> 1);
        }
        return ;
    }
    void down_maintain(int ind) {
        #define LIND(i) (i << 1)
        #define RIND(i) (i << 1 | 1)
        if (LIND(ind) > count) return ;
        int temp = ind;
        if (cmp(data[temp], data[LIND(ind)])) {
            temp = LIND(ind);
        }
        if (RIND(ind) <= count && cmp(data[temp], data[RIND(ind)])) {
            temp = RIND(ind);   
        }
        #undef LIND
        #undef RIND
        if (temp == ind) return ;
        std::swap(data[ind], data[temp]);
        down_maintain(temp);
        return ;
    }
    int front()  const override { return data[1];  }
public:
    priority_queue(CMP_T cmp = less<int>(), int n = 10) : raw_data(new int[n]), data(raw_data - 1), count(0), __size(n), cmp(cmp) {}
    void push(int val) override {
        if (count == __size) {
            expand();
        }
        count += 1;
        data[count] = val;
        up_maintain(count);
        return ;
    }
    void pop() override { 
        if (empty()) return ;
        data[1] = data[count];
        count -= 1;
        down_maintain(1);
        return ;
    }
    bool empty() const override { return count == 0; }
    int top() const override { return data[1]; }
    int size()   const override { return count; }
    void swap(priority_queue &q) {
        std::swap(this->raw_data, q.raw_data);
        std::swap(this->data, q.data);
        std::swap(this->count, q.count);
        std::swap(this->__size, q.__size);
        return ;
    }
    ~priority_queue() {
        if (raw_data) delete[] raw_data;
        return ;
    }
};
ostream &operator<<(ostream &out, const queue &q) {
    out << "queue : ";
    for (int i = 0, j = q.head; i < q.count; i += 1, j += 1) {
        j %= q.__size;
        out << q.data[j] << " ";
    }
    return out;
}
ostream &operator<<(ostream &out, const priority_queue &q) {
    out << "priority_queue : ";
    for (int i = 0; i < q.count; i += 1) {
        out << q.raw_data[i] << " ";
    }
    return out;
}

}
bool cmp(int a, int b) {
    return a > b;
}
int main() {
    int op, val;
    haizei::queue q1;
    haizei::priority_queue q2;
    haizei::priority_queue q3(cmp);
    while (cin >> op) {
        switch(op) {
            case 0: {
                cin >> val;
                q1.push(val);
                q2.push(val);
                q3.push(val);
            } break;
            case 1: {
                cout << "queue front : " << q1.front() << endl;
                cout << "priority(less) top : " << q2.top() << endl;
                cout << "priority(greater) top : " << q3.top() << endl;
                q1.pop();
                q2.pop();
                q3.pop();
            } break;
        }
        cout << q1 << endl;
        cout << q2 << endl;
        cout << q3 << endl;
    }
    return 0;
}
