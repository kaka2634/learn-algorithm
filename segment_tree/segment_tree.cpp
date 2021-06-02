//学习来源： https://www.bilibili.com/medialist/play/ml112583813/BV1cb411t7AM

#include <iostream>
using namespace std;

//定义tree数组的最大长度
const int MAX_N = 1000;

//node 线段树的下标
//[start, end] 线段树node 对应于原数组中的index 区间范围
void build_tree(int arr[], int tree[], int node, int start, int end)
{
    //到达叶节点
    if (start == end)
    {
        tree[node] = arr[start];
        return;
    }

    //mid 左子树和右子树的区间中点
    int mid = (start + end) / 2;
    //node_left node左子树的节点的下标
    int node_left = node * 2 + 1;
    //node_right node右子树的节点下标
    int node_right = node * 2 + 2;

    //递归更新左子树和右子树
    build_tree(arr, tree, node_left, start, mid);
    build_tree(arr, tree, node_right, mid + 1, end);
    //更新node 节点为 两个子树之和, 因为计算结果已经在tree[] 中就不需要函数返回了
    tree[node] = tree[node_left] + tree[node_right];
}

//idx 需要更新的arr的下标
//val 需要更新成的val
void update_tree(int arr[], int tree[], int node, int start, int end, int idx, int val)
{
    //找到目的叶节点
    if (start == end)
    {
        tree[node] = val;
        arr[start] = val;
        return;
    }

    int mid = (start + end) / 2;
    int node_left = node * 2 + 1;
    int node_right = node * 2 + 2;
    //找到对应的idx位置，更新对应子树
    if (idx <= mid)
    {
        update_tree(arr, tree, node_left, start, mid, idx, val);
    }
    else
    {
        update_tree(arr, tree, node_right, mid + 1, end, idx, val);
    }
    //更新根节点的数值
    tree[node] = tree[node_left] + tree[node_right];
}

//[L, R] 想访问的区间和
int query_tree(int arr[], int tree[], int node, int start, int end, int L, int R)
{
    //不在区间 L, R 内
    if (start > R || end < L)
    {
        return 0;
    }

    //完全在L, R 内
    if (start >= L && end <= R)
    {
        return tree[node];
    }

    //到了叶节点, 这里理解上应该在前面这一个条件就会返回了，所以这个返回应该没有用
    if (start == end) {
        return tree[node];
    }

    int mid = (start + end) / 2;
    int node_left = node * 2 + 1;
    int node_right = node * 2 + 2;
    int sum_left = query_tree(arr, tree, node_left, start, mid, L, R);
    int sum_right = query_tree(arr, tree, node_right, mid + 1, end, L, R);
    return sum_left + sum_right;
}

int main()
{
    int arr[] = {1, 3, 5, 7, 9, 11};
    int tree[MAX_N] = {0};

    build_tree(arr, tree, 0, 0, sizeof(arr) / sizeof(*arr) - 1);
    cout << "*********************************" << endl;
    cout << "build tree" << endl;
    for (int i = 0; i <= 14; i++)
    {
        cout << "tree[" << i << "] = " << tree[i] << endl;
    }

    update_tree(arr, tree, 0, 0, sizeof(arr) / sizeof(*arr) - 1, 3, 6);
    cout << "*********************************" << endl;
    cout << "update tree" << endl;
    for (int i = 0; i <= 14; i++)
    {
        cout << "tree[" << i << "] = " << tree[i] << endl;
    }


    int sum = query_tree(arr, tree, 0, 0, sizeof(arr) / sizeof(*arr) - 1, 3, 5);
    cout << "*********************************" << endl;
    cout << "query tree arr[3, 5]  = " << sum <<endl;
}