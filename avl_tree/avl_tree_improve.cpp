#include "avl_tree_improve.h"
#include <algorithm>
#include <iostream>
using namespace std;

//LL平衡旋转 (向右单旋转)
template <class K, class V>
Node<K, V>* AVLTree<K, V>::LL_rotate(Node<K, V>* p)
{
    Node<K, V>* c = p->left;
    p->left = c->right;
    c->right = p;

    p->height = max(get_height(p->left), get_height(p->right)) + 1;
    c->height = max(get_height(c->left), p->height) + 1;
    return c;
}

//RR平衡旋转 (向左单旋转) ，是向右旋转的镜像
template <class K, class V>
Node<K, V>* AVLTree<K, V>::RR_rotate(Node<K, V>* p)
{
    Node<K, V>* c = p->right;
    p->right = c->left;
    c->left = p;

    p->height = max(get_height(p->left), get_height(p->right)) + 1;
    c->height = max(get_height(c->right), p->height) + 1;
    return c;
}

//RL平衡旋转 (先向右后向左双旋转)
template <class K, class V>
Node<K, V>* AVLTree<K, V>::RL_rotate(Node<K, V>* p)
{
    p->right = LL_rotate(p->right);
    return RR_rotate(p);
}

//LR平衡旋转 (先向左后向右双旋转)
template <class K, class V>
Node<K, V>* AVLTree<K, V>::LR_rotate(Node<K, V>* p)
{
    p->left = RR_rotate(p->left);
    return LL_rotate(p);
}

//获取节点的高度
template <class K, class V>
int AVLTree<K, V>::get_height(Node<K, V>* p)
{
    if (p == nullptr)
        return 0;
    return p->height;
}

//获取节点的平衡因子
template <class K, class V>
int AVLTree<K, V>::get_balance_factor(Node<K, V>* p)
{
    return get_height(p->left) - get_height(p->right);
}

//平衡节点
//先看左子树还是右子树，再看是子树的左孩子还是右孩子，决定采用哪种旋转操作
template <class K, class V>
Node<K, V>* AVLTree<K, V>::balance(Node<K, V>* p)
{
    //获取根节点的平衡因子
    int p_factor = get_balance_factor(p);

    //1. 如果左子树树高更高
    if (p_factor > 1) {
        //获取左子树的平衡因子
        int c_factor = get_balance_factor(p->left);

        if (c_factor > 0) {
            //1.1 左子树(L)的左孩子(L)更高
            p = LL_rotate(p);
        } else {
            //1.2 左子树(L)的右孩子(R)更高
            p = LR_rotate(p);
        }
    }

    //2. 如果右子树树高更高
    if (p_factor < -1) {
        //获取左子树的平衡因子
        int c_factor = get_balance_factor(p->right);

        if (c_factor > 0) {
            //2.1 右子树(R)的左孩子(L)更高
            p = RL_rotate(p);
        } else {
            //2.2 右子树(R)的右孩子(R)更高
            p = RR_rotate(p);
        }
    }
    //返回平衡后的根节点
    return p;
}

//插入：相比于一般二叉搜索树，插入后增加了平衡操作
template <class K, class V>
void AVLTree<K, V>::insert(K key, V value)
{
    root = insert(root, key, value);
}

template <class K, class V>
Node<K, V>* AVLTree<K, V>::insert(Node<K, V>* p, K key, V value)
{
    //终结条件1: 到达null节点，需新建节点返回，完成插入
    if (p == nullptr) {
        p = new Node<K, V>(key, value);
        return p;
    }

    //终结条件2：如果key相同，那么只需更新value，这里等同update操作
    if (p->key == key) {
        p->value = value;
        return p;
    }

    //否则就需要继续寻找子树
    if (key < p->key) {
        p->left = insert(p->left, key, value);
    } else {
        p->right = insert(p->right, key, value);
    }

    //注意：这里相比一般二叉搜索树，在这里增加了平衡语句，这是两者的唯一区别
    //因为平衡操作可能导致根节点变化，同样将返回值用于更新根节点返回
    p = balance(p);

    //插入后还需要更新height
    p->height = max(get_height(p->left), get_height(p->right)) + 1;
    return p;
}

//查找：与一般二叉搜索树相同
template <class K, class V>
Node<K, V>* AVLTree<K, V>::find(K key)
{
    return find(root, key);
}

template <class K, class V>
Node<K, V>* AVLTree<K, V>::find(Node<K, V>* p, K key)
{
    //终结条件: 到达null节点，或者找到对应节点
    if (p == nullptr || p->key == key) {
        return p;
    }

    //根据二叉搜索树的性质继续寻找
    if (key < p->key) {
        return find(p->left, key);
    } else {
        return find(p->right, key);
    }
}

//返回二叉搜索树的最左节点，用于查找右子树中的后继节点（右子树中最小）
template <class K, class V>
Node<K, V>* AVLTree<K, V>::find_min(Node<K, V>* p)
{
    if (p == nullptr)
        return p;
    while (p->left != nullptr) {
        p = p->left;
    }
    return p;
}

//返回前最右节点，用于查找左子树中的前驱节点（左子树中最大）
template <class K, class V>
Node<K, V>* AVLTree<K, V>::find_max(Node<K, V>* p)
{
    if (p == nullptr)
        return p;
    while (p->right != nullptr) {
        p = p->right;
    }
    return p;
}

//删除: 相比于一般二叉搜索树，增加了删除后的平衡操作
template <class K, class V>
void AVLTree<K, V>::remove(K key)
{
    root = remove(root, key);
}

template <class K, class V>
Node<K, V>* AVLTree<K, V>::remove(Node<K, V>* p, K key)
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
        if (p->left == nullptr) {
            Node<K, V>* replace = p->right;
            delete p;
            p = nullptr;
            return replace;
        } else if (p->right == nullptr) {
            Node<K, V>* replace = p->left;
            delete p;
            p = nullptr;
            return replace;
        }

        //3. 剩下就是左右孩子都存在的情况
        //注意： 这里与一般二叉搜索树的区别，在于要根据树高选择前驱/后继节点作为替换节点
        int p_factor = get_balance_factor(p);
        if (p_factor > 0) {
            //3.1 左子树更高,则将根节点的值更换为前驱节点
            Node<K, V>* replace = find_max(p->left);
            p->key = replace->key;
            p->value = replace->value;
            p->left = remove(p->left, replace->key);
        } else {
            //3.2 右子树更高, 则将根节点的值更换为后继节点
            Node<K, V>* replace = find_min(p->right);
            p->key = replace->key;
            p->value = replace->value;
            p->right = remove(p->right, replace->key);
        }

        //注意： 这里需要用else if，因为key的值可能会在前面替换节点时被修改了
    } else if (key < p->key) {
        p->left = remove(p->left, key);

    } else {
        p->right = remove(p->right, key);
    }
    //注意： 最后要对节点进行平衡操作
    p = balance(p);
    return p;
}

//遍历
template <class K, class V>
void AVLTree<K, V>::pre_order_traverse(Node<K, V>* p)
{
    if (p == nullptr)
        return;
    cout << p->key << " ";
    pre_order_traverse(p->left);
    pre_order_traverse(p->right);
}

template <class K, class V>
void AVLTree<K, V>::mid_order_traverse(Node<K, V>* p)
{

    if (p == nullptr)
        return;
    mid_order_traverse(p->left);
    cout << p->key << " ";
    mid_order_traverse(p->right);
}

template <class K, class V>
void AVLTree<K, V>::print()
{
    cout << "Pre order traverse: ";
    pre_order_traverse(root);
    cout << endl;
    cout << "Mid order traverse: ";
    mid_order_traverse(root);
}

//判断是否平衡
template <class K, class V>
bool AVLTree<K, V>::is_balance()
{
    return is_balance(root);
}

template <class K, class V>
bool AVLTree<K, V>::is_balance(Node<K, V>* p)
{
    if (p == nullptr)
        return true;

    int p_factor = get_balance_factor(p);
    return p_factor > -2 && p_factor < 2
        && is_balance(p->left)
        && is_balance(p->right);
}

int main()
{
    AVLTree<int, int> tree;
    cout << "*************************************" << endl;
    cout << "After insert 10, 40, 30, 60, 90, 70, 20, 50, 80:" << endl;
    int arr[] = { 10, 40, 30, 60, 90, 70, 20, 50, 80 };
    for (int i = 0; i < 9; i++) {
        tree.insert(arr[i], i);
    }
    tree.print();
    cout << endl;
    cout << "*************************************" << endl;
    int arr2[] = { 80, 10, 50, 40 };
    for (int i = 0; i < 4; i++) {
        tree.remove(arr2[i]);
        cout << "Remove " << arr2[i] << " tree balance check: " << tree.is_balance() << endl;
    }
    cout << "*************************************" << endl;
    cout << "After remove 80, 10, 50, 40:" << endl;
    tree.print();
    return 0;
}