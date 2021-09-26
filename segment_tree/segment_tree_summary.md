# 线段树总结

目的：
1. 修改数组中的某个值
2. 区域查询


区域最小值线段树
区域和线段树

注意点：
1. 包括的方法：
```
void build()
void modify(int p, int value)
int query(int l, int r)
```
此外还存在区域修改
```
void modify(int l, int r, int value)
```

2. 下标计算
- 下标从 1 开始
- 因为是完美二叉树，左孩子下标一定是偶数，右孩子下标一定是奇数 （根节点除外，根节点是奇数）

- 根节点 i 
两孩子子节点下标 2 * i, 2 * i + 1 
位运算表示： i << 1, i << 1 | 1;

- 孩子节点为 i (对于输入idx 需要增加 n  i = idx + n)
另一个孩子节点下标为 i ^ 1
根节点下标为 i >> 1

参考：https://codeforces.com/blog/entry/18051


实现上：
1. 先更新叶子，再到根节点

2. 求范围时候的加入res的条件很关键，尤其right的判断
```C++
  //注意这里是左闭右闭区间
  while(left <= right){
      //如果left 是右孩子，left加入res，并移除该节点，left++
      if(left & 1) res += arr[left++];
      //如果right 是左孩子，同样right加入res，并移除该节点，right--
      if(!right & 1) res += arr[right--];
      left = left >> 1;
      right = right >> 1;
  }
```

什么情况下，无法使用线段树？
如果我们删除或者增加区间中的元素，那么区间的大小将发生变化，此时是无法使用线段树解决这种问题的。