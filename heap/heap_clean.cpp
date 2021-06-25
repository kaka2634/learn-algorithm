#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 10000;

// 整洁代码
// 参考：https://zhuanlan.zhihu.com/p/187618450

class heap {
private:
    int arr[MAX_N];
    int max_idx = 0;

    //上浮
    void swim(int idx)
    {
        int val = arr[idx];
        while (idx / 2 > 0 && arr[idx / 2] < val) {
            arr[idx] = arr[idx / 2];
            idx = idx / 2;
        }
        arr[idx] = val;
    }

    //下沉
    void sink(int idx)
    {
        int val = arr[idx];
        //更新：通过son函数找到更大的儿子，parent直接与最大儿子比较
        int son_idx = son(idx);
        //注意： 这里用val 而不是用arr[idx]去和arr[son_idx]比较_
        while (son_idx <= max_idx && val < arr[son_idx]) {
            arr[idx] = arr[son_idx];
            idx = son_idx;
            son_idx = son(idx);
        }
        arr[idx] = val;
    }

    int son(int idx)
    {
        return idx * 2 + (idx * 2 + 1 <= max_idx && arr[idx * 2 + 1] > arr[idx * 2]);
    }

public:
    //插入数
    void push(int val)
    {
        //在数组最后插入, 数组下标从1开始
        arr[++max_idx] = val;
        //将最后一位数上浮
        swim(max_idx);
    }

    //pop堆顶
    int pop()
    {
        //先记录返回值
        int res = arr[1];
        //将最后的值放到堆顶, 并删除最后一位数
        arr[1] = arr[max_idx--];
        //然后将堆顶的数向下下沉
        sink(1);
        return res;
    }

    void print()
    {
        for (int i = 1; i <= max_idx; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    heap h;

    int push_time = 10;
    for (int i = 1; i < push_time; i++) {
        h.push(i);
    }
    h.print();

    for (int i = 1; i < push_time; i++) {
        cout << h.pop() << " ";
    }

    return 0;
}