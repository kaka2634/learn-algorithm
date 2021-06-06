//来源： leetcode 208.实现Trie树 https://leetcode-cn.com/problems/implement-trie-prefix-tree/

#include <iostream>
#include <vector>
using namespace std;

class Trie
{
private:
    vector<Trie *> next; //next 数组，大小初始化为26个字母
    bool isEnd; //记录该节点是否是一个word 的结尾

public:
    Trie() : next(26), isEnd(false)
    {
    }


    void insert(string word)
    {
        Trie *node = this; //node用于遍历Trie 树
        for (char c : word) 
        {
            if (node->next[c - 'a'] == nullptr) //判断关键
            {
                node->next[c - 'a'] = new Trie();
            }
            node = node->next[c - 'a'];
        }
        node->isEnd = true; //结尾的节点isEnd设置为true，不一定是叶节点就是true，中间节点叶可能是word 的结尾
    }


    bool search(string word)
    {
        Trie *node = this;
        for (char c : word)
        {
            if (node->next[c - 'a'] == nullptr)
            {
                return false;
            }
            node = node->next[c - 'a'];
        }
        return node->isEnd; //返回该节点是不是word 
    }


    bool startsWith(string prefix)
    {
        Trie *node = this;
        for (char c : prefix)
        {
            if (node->next[c - 'a'] == nullptr)
            {
                return false;
            }
            node = node->next[c - 'a'];
        }
        return true; //与seach word 区别只在返回，perfix 直接返回的是true 
    }
};

int main()
{
    Trie* trie = new Trie();
    trie->insert("apple");
    cout<<trie->search("apple")<<endl;   // 返回 True
    cout<<trie->search("app")<<endl;     // 返回 False
    cout<<trie->startsWith("app")<<endl; // 返回 True
    trie->insert("app");
    cout<<trie->search("app")<<endl; // 返回 True

}