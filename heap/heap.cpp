#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 10000;

class heap {
private:
    int arr[MAX_N];
    int max_idx = 0;

    //用于交换数组中两个值
    void swap(int idx1, int idx2)
    {
        arr[idx1] = arr[idx1] + arr[idx2];
        arr[idx2] = arr[idx1] - arr[idx2];
        arr[idx1] = arr[idx1] - arr[idx2];
    }

    //上浮
    void swim(int idx)
    {
        while (idx / 2 > 0 && arr[idx / 2] < arr[idx]) {
            swap(idx / 2, idx);
            idx = idx / 2;
        }
    }

    //下沉
    void sink(int idx)
    {
        //只要有儿子比父亲更大，就不断向下下沉
        while ((idx * 2 <= max_idx && arr[idx * 2] > arr[idx])
            || (idx * 2 + 1 <= max_idx && arr[idx * 2 + 1] > arr[idx])) {
            //选择儿子中更大的数与父亲交换，两个儿子也需要比较
            if (arr[idx * 2] > arr[idx * 2 + 1] || idx * 2 + 1 > max_idx) {
                swap(idx * 2, idx);
                //不要忘记更新idx
                idx = idx * 2;
            } else {
                swap(idx * 2 + 1, idx);
                idx = idx * 2 + 1;
            }
            
        }
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
        //将堆顶与数组最后一个数交换
        swap(1, max_idx);
        //删除最后一位数
        max_idx--;
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