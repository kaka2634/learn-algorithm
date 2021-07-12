#include "avl_tree_improve.h"
#include <iostream>
using namespace std;

//LL平衡旋转 (向右单旋转)
//假定根节点为A，左孩子为B, 因为左孩子B的左子树BL插入节点导致了不平衡
template <class K, class V>
Node<K, V>* AVLTree<K, V>::LL_rotate(Node<K, V>* p)
{
    //1.先记录左孩子B到temp
    Node<K, V>* temp = p->left;
    //2. 将左孩子B的右子树BR 连接 成为节点A的左子树AL
    p->left = temp->right;
    //3. 将左孩子B的右孩子更换成为节点A -> 左孩子B向右实现了旋转
    temp->right = p;
    //4. 返回左孩子B作为根节点
    return temp;
}

//RR平衡旋转 (向左单旋转) -> 是向右旋转的镜像
//假定根节点为A，右孩子为B, 因为右孩子B的右子树BR插入节点导致了不平衡
template <class K, class V>
Node<K, V>* AVLTree<K, V>::RR_rotate(Node<K, V>* p)
{
    //1.先记录右孩子B到temp
    Node<K, V>* temp = p->right;
    //2. 将右孩子B的左子树BL 连接 成为节点A的右子树AR
    p->right = temp->left;
    //3. 将右孩子B的左孩子更换成为节点A -> 右孩子B向左实现了旋转
    temp->left = p;
    //4. 返回右孩子B作为根节点
    return temp;
}

//RL平衡旋转 (先向右后向左双旋转)
//假定根节点为A，右孩子为B, 因为右孩子B的左孩子C的子树CL/CR插入节点导致了不平衡
template <class K, class V>
Node<K, V>* AVLTree<K, V>::RL_rotate(Node<K, V>* p)
{
    //1. 先对右孩子B使用LL_rotate, 向右旋转将左孩子C提上来，A的右孩子将从B变为C
    p->right = LL_rotate(p->right);
    //2. 再对根节点A使用RR_rotate, 向左旋转将此时根节点A的右孩子C提上来
    return RR_rotate(p);
}

//LR平衡旋转 (先向左后向右双旋转)
//假定根节点为A，左孩子为B, 因为左孩子B的右孩子的子树CL/CR插入节点导致了不平衡
template <class K, class V>
Node<K, V>* AVLTree<K, V>::LR_rotate(Node<K, V>* p)
{
    //1. 先对左孩子B使用RR_rotate, 向左旋转将右孩子C提上来，A的左孩子将从B变为C
    p->left = RR_rotate(p->left);
    //2. 再对根节点A使用LL_rotate, 向右旋转将此时根节点A的左孩子C提上来
    return LL_rotate(p);
}

//获取节点的高度 -> 递归
template <class K, class V>
int AVLTree<K, V>::get_height(Node<K, V>* p)
{
    if (p == nullptr)
        return 0;
    int left = get_height(p->left);
    int right = get_height(p->right);
    return left > right ? left + 1 : right + 1;
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

//插入：插入后增加了平衡操作
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
    // int arr2[] = { 80, 10, 50, 40 };
    // cout << endl;
    // cout << "*************************************" << endl;
    // cout << "After remove 80, 10, 50, 40:" << endl;
    // for (int i = 0; i < 4; i++) {
    //     tree.remove(arr2[i]);
    // }
    // tree.print();
    return 0;
}