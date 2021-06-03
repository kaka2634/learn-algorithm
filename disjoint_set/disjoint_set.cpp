//学习来源： https://www.bilibili.com/video/BV13t411v7Fs?p=1

#include <iostream>
using namespace std;

const int MAX_N = 6;

//初始化均为-1, 表示都是根节点
int init(int parent[])
{
    for (int i = 0; i < MAX_N; i++)
    {
        parent[i] = -1;
    }
}

//递归截止是parent[x] == -1 时返回
//使用迭代，就新建变量x_root保存记录，避免递归overflow,
int find_root(int x, int parent[])
{
    int x_root = x;
    while (parent[x_root] != -1)
    {
        x_root = parent[x_root];
    }
    return x_root;
}

//将基于x和y的两个节点合并
//返回1 说明合并成功
//返回0 说明合并失败，两个节点已经存在一个集合了 -> 如果连接这两个节点，说明必定成环
int union_vertices(int x, int y, int parent[])
{
    int x_root = find_root(x, parent);
    int y_root = find_root(y, parent);
    if (x_root == y_root)
        return 0;

    //将x的根节点接入y的根节点
    parent[x_root] = y_root;
    return 1;
}

int main()
{
    int parent[MAX_N] = {};

    int edges[6][2]{
        {0, 1}, {1, 2}, {3, 4}, {1, 3}, {2, 4}, {2, 5}};

    init(parent);

    for (int i = 0; i < 6; i++)
    {
        int x = edges[i][0];
        int y = edges[i][1];
        if (union_vertices(x, y, parent) == 0)
        {
            cout << "Found Cycle" << endl;
            return 0;
        }
        
    }
    cout << "Not Found Cyclic" << endl;
    return 0;
}