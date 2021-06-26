#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 10000;

// 提升: 记录需要上浮/下沉的值，找到合适的位置再放置，而不是每次都去交换
// 思路类似 插入排序对比于冒泡排序，交换次数要更少

class heap {
private:
    int arr[MAX_N];
    int max_idx = 0;

    //上浮
    void swim(int idx)
    {
        //更新1：先记录上浮的值
        int val = arr[idx];
        //更新2： 这里要改为与val的比较
        while (idx / 2 > 0 && arr[idx / 2] < val) {
            //更新3： 将parent先往下移，给val让位
            arr[idx] = arr[idx / 2];
            idx = idx / 2;
        }
        //更新4： 最后再将val 放入合适位置
        arr[idx] = val;
    }

    //下沉
    void sink(int idx)
    {
        //更新1：先记录下沉的值
        int val = arr[idx];
        //更新2：这里要改为与val的比较
        while ((idx * 2 <= max_idx && arr[idx * 2] > val)
            || (idx * 2 + 1 <= max_idx && arr[idx * 2 + 1] > val)) {
            //选择儿子中更大的数与父亲交换，两个儿子也需要比较
            if (arr[idx * 2] > arr[idx * 2 + 1] || idx * 2 + 1 > max_idx) {
                //更新3： 将儿子上移，给val 让位
                arr[idx] = arr[idx * 2];
                idx = idx * 2;
            } else {
                arr[idx] = arr[idx * 2 + 1];
                idx = idx * 2 + 1;
            }
        }
        //更新4：最后再将val 放入合适位置
        arr[idx] = val;
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