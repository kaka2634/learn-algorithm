#include "black_red_tree_recursive.h"
#include <iostream>

//左旋
template <class K, class V>
Node<K, V>* BRTree<K, V>::rotate_left(Node<K, V>* p)
{
    Node<K, V>* temp = p->right;
    p->right = temp->left;
    temp->left = p;
    return temp;
}

//右旋
template <class K, class V>
Node<K, V>* BRTree<K, V>::rotate_right(Node<K, V>* p)
{
    Node<K, V>* temp = p->left;
    p->left = temp->right;
    temp->right = p;
    return temp;
}

//插入
template <class K, class V>
void BRTree<K, V>::insert(K key, V value)
{

    root = insert(root, key, value);
    //插入情景1：红黑树为空树，需插入黑色节点
    root->color = BLACK;
}

template <class K, class V>
Node<K, V>* BRTree<K, V>::insert(Node<K, V>* p, K key, V value)
{
    //终结条件1: 到达null节点，需新建节点返回，完成插入
    if (p == nullptr) {
        p = new Node<K, V>(key, value, RED);
        return p;
    }

    //终止条件2&插入情景2: key已经存在并且找到，则直接更新value, 相当于更新操作
    if (p->key == key) {
        p->value = value;
        return p;
    }

    //否则，继续利用递归寻找合适位置插入
    if (key < p->key) {
        p->left = insert(p->left, key, value);
        //插入后，可能需要平衡操作
        p = insert_balance(p, p->left, p->right);
    } else {
        p->right = insert(p->right, key, value);
        p = insert_balance(p, p->right, p->left);
    }
    //返回子树根节点p用于更新
    return p;
}

// pp: grandparent 祖父节点
// p : parent 父节点
// c : child 孩子节点
// u : uncle 叔叔节点
template <class K, class V>
Node<K, V>* BRTree<K, V>::insert_balance(Node<K, V>* pp, Node<K, V>* p, Node<K, V>* u)
{
    //判断是否有红色节点的儿子
    Node<K, V>* c = nullptr;
    if (p->left != nullptr && p->left->color == RED) {
        c = p->left;
    } else if (p->right != nullptr && p->right->color == RED) {
        c = p->right;
    }

    //插入情景4：插入结点的父结点为红节点, 同时存在也为红色节点的儿子
    if (p->color == RED && c != nullptr) {

        //如果父节点是祖父节点的左孩子
        if (p == pp->left) {
            //插入情景4.1：叔叔结点存在并且为红结点
            if (u != nullptr && u->color == RED) {
                u->color = BLACK;
                p->color = BLACK;
                pp->color = RED;
                return pp;
            }

            //插入情景4.2: 叔叔节点不存在或者为黑色节点，父节点是祖父节点的左孩子 （L)
            //插入情景4.2.2: 插入结点是其父节点的右儿子 （L-R型）
            if (c == p->right) {
                //先进行左旋，使之成为4.2.1场景
                p = rotate_left(p);
                pp->left = p;
            }

            //插入情景4.2.1: 插入结点是其父节点的左儿子 （L-L型）
            pp = rotate_right(pp);
            //变色
            pp->color = BLACK;
            pp->right->color = RED;

        } else {
            //如果父节点是祖父节点的右孩子

            //插入情景4.1：叔叔结点存在并且为红结点
            if (u != nullptr && u->color == RED) {
                u->color = BLACK;
                p->color = BLACK;
                pp->color = RED;
                return pp;
            }

            //插入情景4.3: 叔叔节点不存在或者为黑色节点，且父节点是祖父节点的右孩子 （R）
            //插入情景4.3.2: 插入结点是其父节点的左儿子 （R-L型）
            if (c == p->left) {
                //先进行左旋，使之成为4.2.1场景
                p = rotate_right(p);
                pp->right = p;
            }

            //插入情景4.3.1: 插入结点是其父节点的右儿子 （R-R型）
            pp = rotate_left(pp);
            //变色
            pp->color = BLACK;
            pp->left->color = RED;
        }
    }

    //插入情景3：如果插入的父节点为黑色，那么则不需要做任何调整
    return pp;
}

//遍历
template <class K, class V>
void BRTree<K, V>::pre_order_traverse(Node<K, V>* p)
{
    if (p == nullptr)
        return;
    pre_order_traverse(p->left);
    std::cout << "Key: " << p->key << "Color: " << p->color << std::endl;
    pre_order_traverse(p->right);
}

template <class K, class V>
void BRTree<K, V>::mid_order_traverse(Node<K, V>* p)
{

    if (p == nullptr)
        return;
    std::cout << "Key: " << p->key << "Color: " << p->color << std::endl;
    mid_order_traverse(p->left);
    mid_order_traverse(p->right);
}

template <class K, class V>
void BRTree<K, V>::print()
{
    std::cout << "pre order: " << std::endl;
    pre_order_traverse(root);
    std::cout << "mid order: " << std::endl;
    mid_order_traverse(root);
}

template <class K, class V>
bool BRTree<K, V>::is_balance()
{
    if (root != nullptr && root->color == RED)
        return false;

    int target_black_num = 0;
    Node<K, V>* p = root;
    while (p != nullptr) {
        if (p->color == BLACK)
            target_black_num++;
        p = p->left;
    }

    //cur_black_num 这里要初始化为1， 因为root没有计入总数
    return is_balance(root, root->left, 1, target_black_num)
        && is_balance(root, root->right, 1, target_black_num);
}

template <class K, class V>
bool BRTree<K, V>::is_balance(Node<K, V>* p, Node<K, V>* c, int cur_black_num, int target_black_num)
{
    if (c == nullptr)
        return cur_black_num == target_black_num;
    if (c->color == RED && p->color == RED)
        return false;
    if (c->color == BLACK)
        cur_black_num++;
    return is_balance(c, c->left, cur_black_num, target_black_num)
        && is_balance(c, c->right, cur_black_num, target_black_num);
}

int main()
{
    BRTree<int, int> tree;
    int arr[] = { 10, 40, 30, 60, 90, 70, 20, 50, 80 };
    for (int i = 0; i < 9; i++) {
        tree.insert(arr[i], i);
    }
    std::cout << "After inserted, tree is" << std::endl;
    tree.print();
    std::cout << tree.is_balance() << std::endl;
    return 0;
}