//来源： leetcode 211. 添加与搜索单词  https://leetcode-cn.com/problems/design-add-and-search-words-data-structure/
#include <iostream>
#include <vector>
using namespace std;

class TrieNode
{
public:
    vector<TrieNode *> next;
    bool isWord;
    TrieNode() : next(26), isWord(false)
    {
    }
};

class WordDictionary
{
private:
    TrieNode *root;

public:
    WordDictionary()
    {
        root = new TrieNode();
    }

    void addWord(string word)
    {
        TrieNode *node = root;
        for (char c : word)
        {
            if (node->next[c - 'a'] == nullptr)
            {
                node->next[c - 'a'] = new TrieNode();
            }
            node = node->next[c - 'a'];
        }
        node->isWord = true;
    }

    //修改search function 为递归方式，这样可以分为多支search
    bool search(string word)
    {
        return match(word, 0, root);
    }

    bool match(string word, int start, TrieNode *node)
    {
        //递归终结条件
        if (start == word.size())
        {
            return node->isWord;
        }
        //如果是通配符，则需要每一种情况都去match
        if (word[start] == '.')
        {
            for (int i = 0; i < 26; i++)
            {
                if (node->next[i] != nullptr && match(word, start + 1, node->next[i]))
                {
                    return true;
                }
            }
            return false;
        }
        else
        {
            //如果不是通配符，递归调用到下一个节点
            int i = word[start] - 'a';
            return node->next[i] != nullptr && match(word, start + 1, node->next[i]);
        }
    }
};

int main()
{
    WordDictionary wordDictionary;
    wordDictionary.addWord("bad");
    wordDictionary.addWord("dad");
    wordDictionary.addWord("mad");
    cout<<wordDictionary.search("pad")<<endl; // return False
    cout<<wordDictionary.search("bad")<<endl; // return True
    cout<<wordDictionary.search(".ad")<<endl; // return True
    cout<<wordDictionary.search("b..")<<endl; // return True
}
