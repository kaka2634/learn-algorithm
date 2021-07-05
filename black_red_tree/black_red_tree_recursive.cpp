#include "black_red_tree_recursive.h"
#include <iostream>

//左旋
template <class K, class V>
Node<K, V>* BRTree<K, V>::rotate_left(Node<K, V>* p)
{
    Node<K, V>* pr = p->right;
    p->right = pr->left;
    //因为有parent指针，所以增加了对parent指针的处理
    if (p->right != nullptr) {
        p->right->parent = p;
    }

    pr->parent = p->parent;

    pr->left = p;
    p->parent = pr;
    //返回更新后的根节点pr
    return pr;
}

//右旋
template <class K, class V>
Node<K, V>* BRTree<K, V>::rotate_right(Node<K, V>* p)
{
    Node<K, V>* pl = p->left;
    p->left = pl->right;
    if (p->left != nullptr) {
        p->left->parent = p;
    }

    pl->parent = p->parent;

    pl->right = p;
    p->parent = pl;
    return pl;
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
    //终止条件1: 如果key没有存在，那么则需要新建Node放入，再返回该节点用于更新树
    if (p == nullptr) {
        p = new Node<K, V>(key, value, RED);
        return p;
    }

    //终止条件2&插入情景2: key已经存在并且找到，则直接更新value
    if (p->key == key) {
        p->value = value;
        return p;
    }

    //继续利用递归寻找合适位置插入
    if (key < p->key) {
        //左子树寻找合适位置, 同时接收更新的左子树
        p->left = insert(p->left, key, value);
        p->left->parent = p;
        //插入后，以p为根节点的子树可能会被打破平衡，所以需要进行平衡操作
        p = insert_balance(p, p->left);
    } else {
        //右子树寻找合适位置, 同时接收更新的左子树
        p->right = insert(p->right, key, value);
        p->right->parent = p;
        //插入后，以p为根节点的子树可能会被打破平衡，所以需要进行平衡操作
        p = insert_balance(p, p->right);
    }

    //返回子树根节点p用于更新
    return p;
}

//Node p: parent, Node s: son
template <class K, class V>
Node<K, V>* BRTree<K, V>::insert_balance(Node<K, V>* p, Node<K, V>* s)
{
    //插入情景3：如果插入的父节点为黑色，那么则不需要做任何调整
    //插入情景4：插入结点的父结点为红节点, 由于递归需要同时判断儿子节点也为红色
    if (s->color == RED && p->color == RED) {
        //如果p节点是红色，由红黑树性质，那么一定存在p_parent节点
        Node<K, V>* p_parent = p->parent;

        //如果父节点是祖父节点的左孩子
        if (p == p_parent->left) {
            Node<K, V>* s_uncle = p_parent->right;
            //插入情景4.1：叔叔结点存在并且为红结点
            if (s_uncle != nullptr && s_uncle->color == RED) {
                s_uncle->color = BLACK;
                p->color = BLACK;
                p_parent->color = RED;
                return p;
            }

            //插入情景4.2: 叔叔节点不存在或者为黑色节点，父节点是祖父节点的左孩子 （L)
            //插入情景4.2.2: 插入结点是其父节点的右儿子 （L-R型）
            if (s == p->right) {
                //先进行左旋，使之成为4.2.1场景
                p = rotate_left(p);
                p_parent = p->parent;
                p_parent->left = p;
            }

            //插入情景4.2.1: 插入结点是其父节点的左儿子 （L-L型）
            p_parent = rotate_right(p_parent);
            p = p_parent->left;
            //变色
            p_parent->color = BLACK;
            p_parent->right->color = RED;
            return p_parent;

        } else {
            //如果父节点是祖父节点的右孩子
            Node<K, V>* s_uncle = p_parent->left;
            //插入情景4.1：叔叔结点存在并且为红结点
            if (s_uncle != nullptr && s_uncle->color == RED) {
                s_uncle->color = BLACK;
                p->color = BLACK;
                p_parent->color = RED;
                return p;
            }

            //插入情景4.3: 叔叔节点不存在或者为黑色节点，且父节点是祖父节点的右孩子 （R）
            //插入情景4.3.2: 插入结点是其父节点的左儿子 （R-L型）
            if (s == p->left) {
                //先进行左旋，使之成为4.2.1场景
                p = rotate_right(p);
                p_parent = p->parent;
                p_parent->right = p;
            }

            //插入情景4.3.1: 插入结点是其父节点的右儿子 （R-R型）
            p_parent = rotate_left(p_parent);
            //变色
            p_parent->color = BLACK;
            p_parent->left->color = RED;
            return p_parent;
        }
    }
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
    int arr[] = { 10, 40, 30 };
    for (int i = 0; i < 3; i++) {
        tree.insert(arr[i], i);
    }
    tree.print();
    return 0;
}