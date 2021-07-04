#include "black_red_tree.h"

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
    //插入情景1：红黑树为空树，需插入黑色节点
    if (root == nullptr) {
        root = new Node<K, V>(key, value, BLACK);
    }
    root = insert(root, key, value);
}

template <class K, class V>
Node<K, V>* BRTree<K, V>::insert(Node<K, V>* p, K key, V value)
{
    //终止条件1: 如果key没有存在，那么则需要新建Node放入，再返回该节点用于更新树
    if (p == nullptr) {
        Node<K, V> node = new Node<K, V>(key, value, RED);
        return node;
    }

    //终止条件2&插入情景2: key已经存在并且找到，则直接更新value
    if (p->key == key) {
        p->value = value;
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
    //插入情景3： 如果插入的父节点为黑色，那么则不需要做任何调整
    //插入情景4：
    if (s->color == RED && p->color == RED) {
        //如果p节点是红色，由红黑树性质，那么一定存在p_parent节点
        Node* p_parent = p->parent;

        //如果父节点是祖父节点的左孩子
        if (p == p_parent->left) {
            s_uncle = p_parent->right;
        } else {
            s_uncle = p_parent->left;
        }
        //插入情景4.1：叔叔结点存在并且为红结点
        if (s_uncle != nullptr && s_uncle->color == RED) {
            s_uncle->color = BLACK;
            p ->color = BLACK;
            p_parent->color = RED;
            return;
        }
    }
}

int main()
{
    return 0;
}