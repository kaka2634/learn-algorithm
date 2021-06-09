//学习来源： https://www.bilibili.com/video/BV1hW411a7ys?t=10

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void prefix_table(string pattern, vector<int>& prefix)
{
    prefix[0] = 0;
    int len = 0;
    int i = 1;
    int n = pattern.size();
    while (i < n) {
        if (pattern[i] == pattern[len]) {
            len++;
            prefix[i] = len;
            i++;
        } else {
            if (len > 0) {
                len = prefix[len - 1]; //不匹配时，对自己使用KMP计算
            } else {
                prefix[i] = 0; //len到0都没有找到公共前后缀，那么直接置0，下一个
                i++;
            }
        }
    }
}

void move_prefix_table(vector<int>& prefix)
{
    int n = prefix.size();
    for (int i = n - 1; i > 0; i--) {
        prefix[i] = prefix[i - 1];
    }
    prefix[0] = -1;
}

void print_array(vector<int>& arr)
{
    for (int a : arr) {
        cout << a;
    }
    cout << endl;
}


void kmp_search(string text, string pattern)
{
    int m = text.size();
    int n = pattern.size();
    int i = 0, j = 0;
    vector<int> prefix(n);
    prefix_table(pattern, prefix);
    move_prefix_table(prefix);

    while (i < m) {
        if (j == n - 1 && text[i] == pattern[j]) {
            cout << "Found match pattern in text [ " << i - j << " ]"<<endl;
            j = prefix[j]; //继续匹配
        }
        if (text[i] == pattern[j]) {
            i++;
            j++;
        } else {
            //不匹配时，可以看跟构造prefix table 时，是一样的思路
            //只不过j右移了，所以不需要减一
            j = prefix[j];
            if (j == -1) { //如果没有匹配那么右移
                i++;
                j++;
            }
        }
    }
}


int main()
{
    string text = "AACABABCABAACABDCABABCABAA";
    string pattern = "ABABCABAA";

    kmp_search(text, pattern);
    // vector<int> prefix(pattern.size());
    // prefix_table(pattern, prefix);
    // cout << "Prefix table: " << endl;
    // print_array(prefix);
    // move_prefix_table(prefix);
    // cout << "Prefix table After move:" << endl;
    // print_array(prefix);
    return 0;
}