#include<iostream>
#include<vector>
using namespace std;

int n; //长度
vector<int> arr; //树状数组
vector<int> nums;//原数组

/**** helper functions ***/
int lowbit(int x){
    return x & -x;
}

//返回 0 - x 下标的区间和
int query(int idx){
    int res = 0;
    for(int i = idx; i > 0; i -= lowbit(i)){
        res += arr[i];
    }
    return res;
}


void add(int idx, int value){
    for(int i = idx; i <= n; i += lowbit(i)){
        arr[i] += value;
    } 
}

/**** public functions****/
void build(){
    n = nums.size();
    arr.resize(n + 1); 
    for(int i = 0; i < n; i++){
        //注意下标要从1开始
        add(i + 1, nums[i]);
    }
}


void modify(int idx, int value){
    add(idx + 1, value - nums[idx]);
    nums[idx] = value;
}

int query(int l, int r){
    return query(r + 1) - query(l);
}

int main(){

}

