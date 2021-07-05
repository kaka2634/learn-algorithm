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
    if (root == nullptr) {
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
                p = s->parent;
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

//删除
template <class K, class V>
void BRTree<K, V>::remove(K key)
{
    Node<K, V>* p = root;
    while (p != nullptr) {
        //找到要删除的目标节点
        if (key == p->key) {
            //删除情景1：若删除结点无子结点，直接删除
            if (p->left == nullptr && p->right == nullptr) {
                //平衡删除
                remove_balance(p);
                //先将parent的链接断开
                if (p->parent->left == p) {
                    p->parent->left = nullptr;
                } else {
                    p->parent->right = nullptr;
                }
                delete p;
                p = nullptr;
                return;
            }

            //删除情景2：若删除结点只有一个子结点，用子结点替换删除结点
            Node<K, V>* replace;
            if (p->left == nullptr) {
                replace = p->right;
                //将替换节点值到需要删除节点的位置
                p->key = replace->key;
                p->value = replace->value;
                //移到遍历指针p
                p = p->right;
            } else if (p->right == nullptr) {
                replace = p->left;
                p->key = replace->key;
                p->value = replace->value;
                p = p->left;
            } else {
                //删除情景3: 若删除结点有两个子结点，用后继结点（大于删除结点的最小结点）替换删除结点
                replace = find_min(p->right);
                p->key = replace->key;
                p->value = replace->value;
                p = p->right;
            }

            //将所寻找的key修改为替换节点的key, 从而继续执行remove 移除掉替换节点
            key = replace->key;
        }
        //继续寻找子树， 这里一定要用else，因为key在前面相等时会被修改
        else if (key < p->key) {
            p = p->left;
        } else {
            p = p->right;
        }
    }
    return;
}

//Node p: parent, s: son, pp: gandparent u:uncle b: brother
template <class K, class V>
void BRTree<K, V>::remove_balance(Node<K, V>* s)
{
    //删除情景1：替换结点是红色结点, 没有任何影响，直接删除

    //删除情景2：替换结点是黑结点
    //保证s 不是root 节点
    while (s->color == BLACK && s->parent != nullptr) {
        Node<K, V>* p = s->parent;
        //删除情景2.1 替换结点是其父结点的左子结点
        if (p->left == s) {
            Node<K, V>* b = p->right;
            //删除情景2.1.1：替换结点的兄弟结点是红结点
            if (b->color == RED) {
                b->color = BLACK;
                p->color = RED;
                //变成删除情景2.1.2.3
                p = rotate_left(p);
                b = p->right;
                s = p->left;
            }
            //删除情景2.1.2：替换结点的兄弟结点是黑结点
            if (b->color == BLACK) {
                //删除情景2.1.2.3：替换结点的兄弟结点的子结点都为黑结点(NIL也是黑色节点)
                if ((b->left == nullptr || b->left->color == BLACK)
                    && (b->right == nullptr || b->right->color == BLACK)) {
                    b->color = RED;
                    //p 作为新的替换节点, 继续删除平衡操作
                    s = p;
                } else {
                    //删除情景2.1.2.2：替换结点的兄弟结点的右子结点为黑结点，左子结点为红结点
                    if ((b->right == nullptr || b->right->color == BLACK)) {
                        b->color = RED;
                        if (b->left != nullptr) {
                            b->left->color = BLACK;
                        }
                        //转换为删除情景2.1.2.1
                        b = rotate_right(b); //rotate之后更新新的兄弟节点
                    }

                    //删除情景2.1.2.1：替换结点的兄弟结点的右子结点是红结点，左子结点任意颜色
                    b->color = p->color;
                    p->color = BLACK;
                    if (p->right->color = RED) {
                        p->right->color = BLACK;
                    }
                    p = rotate_left(p);
                    return;
                }
            }
        } else {

            Node<K, V>* b = p->left;
            //删除情景2.2.1：替换结点的兄弟结点是红结点
            if (b->color == RED) {
                b->color = BLACK;
                p->color = RED;
                //变成删除情景2.2.2.3
                p = rotate_right(p);
                b = p->left;
                s = p->right;
            }
            //删除情景2.2.2：替换结点的兄弟结点是黑结点
            if (b->color == BLACK) {
                //删除情景2.2.2.3：替换结点的兄弟结点的子结点都为黑结点(NIL也是黑色节点)
                if ((b->left == nullptr || b->left->color == BLACK)
                    && (b->right == nullptr || b->right->color == BLACK)) {
                    b->color = RED;
                    //p 作为新的替换节点, 继续删除平衡操作
                    s = p;
                } else {
                    //删除情景2.2.2.2：替换结点的兄弟结点的左子结点为黑结点，右子结点为红结点
                    if ((b->left == nullptr || b->left->color == BLACK)) {
                        b->color = RED;
                        if (b->right != nullptr) {
                            b->right->color = BLACK;
                        }
                        //转换为删除情景2.2.2.1
                        b = rotate_left(b); //rotate之后更新新的兄弟节点
                    }

                    //删除情景2.2.2.1：替换结点的兄弟结点的左子结点是红结点，右子结点任意颜色
                    b->color = p->color;
                    p->color = BLACK;
                    if (p->left->color = RED) {
                        p->left->color = BLACK;
                    }
                    p = rotate_right(p);
                    return;
                }
            }
        }
    }
}

template <class K, class V>
Node<K, V>* BRTree<K, V>::find_min(Node<K, V>* p)
{
    if (p == nullptr)
        return p;
    while (p->left != nullptr) {
        p = p->left;
    }
    return p;
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
    int arr[] = { 10, 40, 30, 60, 90, 70, 20, 50, 80 };
    for (int i = 0; i < 9; i++) {
        tree.insert(arr[i], i);
    }
    // tree.print();

    tree.remove(80);
    tree.remove(10);
    tree.remove(50);
    tree.remove(40);
    tree.print();
    return 0;
}