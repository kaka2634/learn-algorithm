#include "black_red_tree.h"
#include <iostream>

//左旋
//     p
//    / \       
//   pl  s
template <class K, class V>
Node<K, V>* BRTree<K, V>::rotate_left(Node<K, V>* p)
{
    Node<K, V>* s = p->right;
    p->right = s->left;
    //因为有parent指针，所以增加了对parent指针的处理
    if (p->right != nullptr) {
        p->right->parent = p;
    }

    //更新grand parent
    s->parent = p->parent;
    if (p->parent == nullptr) {
        root = s;
    } else if (p->parent->left == p) {
        p->parent->left = s;
    } else {
        p->parent->right = s;
    }

    //调整p和s的位置
    s->left = p;
    p->parent = s;

    //返回更新后的子树根节点
    return s;
}

//右旋
template <class K, class V>
Node<K, V>* BRTree<K, V>::rotate_right(Node<K, V>* p)
{
    Node<K, V>* s = p->left;
    p->left = s->right;
    if (p->left != nullptr) {
        p->left->parent = p;
    }

    s->parent = p->parent;
    if (p->parent == nullptr) {
        root = s;
    } else if (p->parent->left == p) {
        p->parent->left = s;
    } else {
        p->parent->right = s;
    }

    s->right = p;
    p->parent = s;
    //返回更新后的子树根节点
    return s;
}

//插入, 二分非递归插入
template <class K, class V>
void BRTree<K, V>::insert(K key, V value)
{
    //插入情景1：红黑树为空树，需插入黑色节点
    if (root ==  nullptr) {
        root = new Node<K, V>(key, value, BLACK);
        return;
    }

    Node<K, V>* p = root;
    while (p != nullptr) {
        //插入情景2: key已经存在并且找到，则直接更新value
        if (p->key == key) {
            p->value = value;
            return;
        }
        //在左子树继续寻找
        if (key < p->key) {
            //找到合适位置插入
            if (p->left == nullptr) {
                p->left = new Node<K, V>(key, value, RED, p);
                //平衡操作
                insert_balance(p->left);
                return;
            }
            p = p->left;
        } else {
            if (p->right == nullptr) {
                p->right = new Node<K, V>(key, value, RED, p);
                insert_balance(p->right);
                return;
            }
            p = p->right;
        }
    }
}

//Node p: parent, s: son, pp: gandparent u:uncle
template <class K, class V>
void BRTree<K, V>::insert_balance(Node<K, V>* s)
{

    //插入情景3：如果插入的父节点为黑色，那么则不需要做任何调整
    //插入情景4：插入结点的父结点为红节点,那么就需要做调整
    Node<K, V>* p = s->parent;
    while (p != nullptr && p->color == RED) {
        //如果p节点是红色，由红黑树性质，那么一定存在p parent节点
        Node<K, V>* pp = p->parent;

        //如果父节点是祖父节点的左孩子
        if (p == pp->left) {
            Node<K, V>* u = pp->right;
            //插入情景4.1：叔叔结点存在并且为红结点
            if (u != nullptr && u->color == RED) {
                u->color = BLACK;
                p->color = BLACK;
                pp->color = RED;
                //调用while 循环继续向上
                s = pp;
                p = s->parent;
                continue;
            }

            //插入情景4.2: 叔叔节点不存在或者为黑色节点，父节点是祖父节点的左孩子 （L)
            //插入情景4.2.2: 插入结点是其父节点的右儿子 （L-R型）
            if (s == p->right) {
                //先进行左旋，使之成为4.2.1场景
                p = rotate_left(p);
                //注意rotate 的之后的p 和 s 的指针指向为止已经改变，如果有需要，应该交换p和s才是正确的含义
                pp = p->parent;
            }

            //插入情景4.2.1: 插入结点是其父节点的左儿子 （L-L型）
            pp = rotate_right(pp);
            //变色
            pp->color = BLACK;
            pp->right->color = RED;
            return;
        } else {
            //如果父节点是祖父节点的右孩子
            Node<K, V>* u = pp->left;
            //插入情景4.1：叔叔结点存在并且为红结点
            if (u != nullptr && u->color == RED) {
                u->color = BLACK;
                p->color = BLACK;
                pp->color = RED;
                //调用while 循环继续向上
                s = pp;
                continue;
            }

            //插入情景4.3: 叔叔节点不存在或者为黑色节点，且父节点是祖父节点的右孩子 （R）
            //插入情景4.3.2: 插入结点是其父节点的左儿子 （R-L型）
            if (s == p->left) {
                //先进行左旋，使之成为4.2.1场景
                p = rotate_right(p);
                pp = p->parent;
            }

            //插入情景4.3.1: 插入结点是其父节点的右儿子 （R-R型）
            pp = rotate_left(pp);
            //变色
            pp->color = BLACK;
            pp->left->color = RED;
            return;
        }
    }
    //最后将根节点设为黑色
    root->color = BLACK;
}

//遍历
template <class K, class V>
void BRTree<K, V>::pre_order_traverse()
{
    pre_order_traverse(root);
}

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
void BRTree<K, V>::mid_order_traverse()
{
    mid_order_traverse(root);
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
    pre_order_traverse();
    std::cout << "mid order: " << std::endl;
    mid_order_traverse();
}

int main()
{
    BRTree<int, int> tree;
    int arr[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
    for (int i = 0; i < 9; i++) {
        tree.insert(arr[i], i);
    }
    tree.print();
    return 0;
}