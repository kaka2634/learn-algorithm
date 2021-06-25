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
        int son_idx = son(idx);
        while (son_idx <= max_idx && arr[idx] < arr[son_idx]) {
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
        arr[++max_idx] = val;
        swim(max_idx);
    }

    //pop堆顶
    int pop()
    {
        int res = arr[1];
        arr[1] = arr[max_idx--];
        sink(1);
        return res;
    }


    // 更新： 修改build heap的方式
    // 使用下沉的方式能够达到 O(n) 的复杂度
    // 而每次插入元素，上浮的方式的复杂度是 O(nlogn)
    void build(int nums[], int n)
    {
        max_idx = n;
        //先将数组一一赋值到heap数组中
        for (int i = 0; i < n; i++) {
            arr[i + 1] = nums[i];
        }
        //从n/2的元素开始，向堆顶遍历，逐个下沉到合适位置
        for (int i = n / 2 ; i > 0; --i) {
            sink(i);
        }
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

    int nums[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int n = 9;

    h.build(nums, n);
    h.print();

    for (int i = 1; i < n + 1; i++) {
        cout << h.pop() << " ";
    }

    return 0;
}