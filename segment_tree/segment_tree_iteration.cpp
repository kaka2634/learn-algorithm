//参考： https://codeforces.com/blog/entry/18051

#include <stdio.h>

const int N = 1e5; //数组长度限制
int n; //数组有效长度
int arr[2 * N];//线段树数组表示

//构建区间和线段树。根为两子节点和（叶子已经赋值了）
void build(){
    //从n - 1开始后向前，求得根的值
    for(int i = n - 1; i > 0; i--) {
        arr[i] = arr[i<<1] + arr[i << 1 | 1];
    }
}

void modify(int p, int value){
    //1、更新对应的叶子的值，对应下标为 n + p
    arr[p + n] = value;
    //2、向上更新所有的根的值 （swim）
    while(p > 1){
        //注意根节点下标，和另一个孩子节点下标的位运算
        arr[p >> 1] = arr[p] + arr[p ^ 1];
        //更新p 为根节点
        p>>=1;
    }
}

// 区间和查询 [l, r)
int query(int l, int r){
    int res = 0;
    l = l + n;
    r = r + n;
    while(l < r){
        //1. 边界处理
        //l是奇数，说明l是右孩子，那么区间一定包括了该节点，但是没包括其parent 节点。（
        if(l & 1) res += arr[l++];
        //r 是奇数，如果r是右孩子，那么区间一定包括了左节点，但是没包括其parent 节点。
        if(r & 1) res += arr[--r];
        //2. 向上记录parent 节点
        //如果 l 是偶数，那么继续向上移到
        l >>= 1;
        r >>= 1;
    }
    return res;
}

int main(){
    scanf("%d", &n);
    //读入叶子节点
    for(int i = 0; i < n; i++){
        scanf("%d", arr + n + i);
    }
    build();
    modify(0, 1);
    printf("%d\n", query(3, 11));
    return 0;
}