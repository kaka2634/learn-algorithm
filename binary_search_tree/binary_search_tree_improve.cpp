#include "binary_search_tree_improve.h"
#include <iostream>
using namespace std;

template <class K, class V>
BSTree<K, V>::BSTree()
{
    root = nullptr;
}

//插入操作：递归版本
template <class K, class V>
void BSTree<K, V>::insert(K key, V value)
{
    insert(root, key, value);
}

template <class K, class V>
Node<K, V>* BSTree<K, V>::insert(Node<K, V>* p, K key, V value)
{
    //终结条件1: 到达null节点，需新建节点返回，完成插入
    if (p == nullptr) {
        p = new Node(key, value);
        return p;
    }

    //终结条件2：如果key相同，那么只需更新value，这里等同update操作
    if (p->key == key) {
        p->value = value;
        return p;
    }

    //否则就需要继续寻找子树
    //注意： 这里使用的技巧，将递归返回的节点用于更新左右子树的值，从而实现递归构造树
    if (key < p->key) {
        p->left = insert(p->left, key, value);
    } else {
        p->right = insert(p->right, key, value);
    }
    return p;
}

//查找：递归版本
template <class K, class V>
Node<K, V>* BSTree<K, V>::find(K key)
{
    return find(root, key);
}

template <class K, class V>
Node<K, V>* BSTree<K, V>::find(K key)
{
    //终结条件: 到达null节点，或者找到对应节点
    if (p == nullptr || p->key == key) {
        return p;
    }

    //根据二叉搜索树的性质继续寻找
    if (key < p->key) {
        return find(p->left, x);
    } else {
        return find(p->right, x);
    }
}

//删除： 递归版本
template <class K, class V>
void BSTree<K, V>::remove(K key)
{
    return remove(root, key);
}

template <class K, class V>
Node<K, V>* BSTree<K, V>::remove(Node<K, V>* p, K key)
{
    //终结条件1: 到达null节点，仍然没能找到，返回nullptr
    if (p == nullptr) {
        return p;
    }

    //终结条件2： 找到删除节点
    if (p->key == key) {
        //1. 如果没有左右孩子，直接删除该节点
        if (p->left == nullptr && p->right == nullptr) {
            delete p;
            p = nullptr;
            return p;
        }
        //2. 如果只有一个孩子，那么直接将孩子节点作为替换节点, 同时删除节点
        // 因为前面已经判断了两个都是nullptr的情况，这里只需判断一个孩子即可
        if (p->left == nullptr) {
            Node* replace = p->right;
            delete p;
            p = nullptr;
            return replace;
        } else if (p->right == nullptr) {
            Node* replace = p->left;
            delete p;
            p = nullptr;
            return replace;
        }

        //3. 剩下就是左右孩子都存在的情况，这里可以寻找后继节点作为替换节点（也可以使用前驱节点）
        Node* replace = find_min(p->right);
        p->key = replace->key;
        p->value = replace->value;
        //注意：这里使用的树节点删除技巧，删除节点需要找到一个替代节点，将替代节点放到删除节点位置从而不会破坏树的性质。
        //再继续调用同样删除操作去将替换节点删除（更换key值），直到整个树在删除节点后满足基本性质。
        if (key < replace->key) {
            p->left = remove(p->left, replace->key);
        } else {
            p->right = remove(p->right, replace->key);
        }
    }
    //注意： 这里需要用else if，因为key的值可能会在前面替换节点时被修改了
    else if (key < p->val) {
        //选择左子树，同时连接删除后的节点
        p->left = remove(p->left, key);
    } else {
        //选择右子树，同时连接删除后的节点
        p->right = remove(p->right, key);
    }
}