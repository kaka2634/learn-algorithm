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

//删除
template <class K, class V>
void BRTree<K, V>::remove(K key)
{
    bool balance_indicator = false;
    root = remove(root, key, balance_indicator);
}

template <class K, class V>
Node<K, V>* BRTree<K, V>::remove(Node<K, V>* p, K key, bool& balance_indicator)
{
    //终结条件1: 到达null节点，仍然没能找到，返回nullptr
    if (p == nullptr) {
        return p;
    }

    //终结条件2： 找到删除节点
    if (p->key == key) {
        //1. 如果没有左右孩子，直接删除该节点
        if (p->left == nullptr && p->right == nullptr) {

            //删除情景2：替换结点是黑结点, 才需要平衡，通过balance_indicator告诉parent节点
            if (p->color == BLACK) {
                balance_indicator = true;
            }
            delete p;
            p = nullptr;
            return p;
        }

        Node<K, V>* replace = nullptr;
        //2. 如果只有一个孩子，那么直接将孩子节点作为替换节点
        if (p->left == nullptr) {
            replace = p->right;
        } else if (p->right == nullptr) {
            replace = p->left;
        } else {
            //3. 剩下就是左右孩子都存在的情况，这里可以寻找后继节点作为替换节点（也可以使用前驱节点）
            replace = find_min(p->right);
        }

        //注意：与二叉搜索树的不同， 对于红黑树，需要将情况2的节点替换而不是直接删除，需要等到到叶子节点才能删除
        p->key = replace->key;
        p->value = replace->value;
        //注意：这里使用的树节点删除技巧，删除节点需要找到一个替代节点，将替代节点放到删除节点位置从而不会破坏树的性质。
        //再继续调用同样删除操作去将替换节点删除（更换key值），直到整个树在删除节点后满足基本性质。
        if (key > replace->key) {
            p->left = remove(p->left, replace->key, balance_indicator);
            if (balance_indicator) {
                p = remove_balance(p, p->right, balance_indicator);
            }
        } else {
            p->right = remove(p->right, replace->key, balance_indicator);
            if (balance_indicator) {
                p = remove_balance(p, p->left, balance_indicator);
            }
        }

    }
    //注意： 这里需要用else if，因为key的值可能会在前面替换节点时被修改了
    //同时，递归删除树同样需要将返回值用于更新左右子树指针
    else if (key < p->key) {
        p->left = remove(p->left, key, balance_indicator);
        if (balance_indicator) {
            p = remove_balance(p, p->right, balance_indicator);
        }

    } else {
        p->right = remove(p->right, key, balance_indicator);
        if (balance_indicator) {
            p = remove_balance(p, p->left, balance_indicator);
        }
    }
    return p;
}

//删除平衡
//p: parent 父节点
//s: sibling 兄弟节点
template <class K, class V>
Node<K, V>* BRTree<K, V>::remove_balance(Node<K, V>* p, Node<K, V>* s, bool& balance_indicator)
{

    //删除情景2.1：替换结点是其父结点的左子结点
    if (p->right == s) {
        //删除情景2.1.1：替换结点的兄弟结点是红结点
        if (s->color == RED) {
            s->color = BLACK;
            p->color = RED;
            //变成删除情景2.1.2.3
            p = rotate_left(p);
            s = p->right;
        }
        //删除情景2.1.2：替换结点的兄弟结点是黑结点
        if (s->color == BLACK) {
            //删除情景2.1.2.3：替换结点的兄弟结点的子结点都为黑结点(NIL也是黑色节点)
            if ((s->left == nullptr || s->left->color == BLACK)
                && (s->right == nullptr || s->right->color == BLACK)) {
                s->color = RED;
                //p 视为新的替换节点, 不改变indicator，返回后继续删除平衡操作
                return p;
            } else {
                //删除情景2.1.2.2：替换结点的兄弟结点的右子结点为黑结点，左子结点为红结点
                if ((s->right == nullptr || s->right->color == BLACK)) {
                    s->color = RED;
                    if (s->left != nullptr) {
                        s->left->color = BLACK;
                    }
                    //转换为删除情景2.1.2.1
                    s = rotate_right(s); //rotate之后更新新的兄弟节点
                    //注意：这里要将新的s链接上p
                    p->right = s;
                }

                //删除情景2.1.2.1：替换结点的兄弟结点的右子结点是红结点，左子结点任意颜色
                s->color = p->color;
                p->color = BLACK;
                if (s->right != nullptr) {
                    s->right->color = BLACK;
                }
                p = rotate_left(p);
                //平衡indicator 清除
                balance_indicator = false;
                return p;
            }
        }
    } else {
        //删除情景2.2.1：替换结点的兄弟结点是红结点
        if (s->color == RED) {
            s->color = BLACK;
            p->color = RED;
            //变成删除情景2.2.2.3
            p = rotate_right(p);
            s = p->left;
        }
        //删除情景2.2.2：替换结点的兄弟结点是黑结点
        if (s->color == BLACK) {
            //删除情景2.2.2.3：替换结点的兄弟结点的子结点都为黑结点(NIL也是黑色节点)
            if ((s->left == nullptr || s->left->color == BLACK)
                && (s->right == nullptr || s->right->color == BLACK)) {
                s->color = RED;
                //p 视为新的替换节点, 不改变indicator，返回后继续删除平衡操作
                return p;
            } else {
                //删除情景2.2.2.2：替换结点的兄弟结点的左子结点为黑结点，右子结点为红结点
                if ((s->left == nullptr || s->left->color == BLACK)) {
                    s->color = RED;
                    if (s->right != nullptr) {
                        s->right->color = BLACK;
                    }
                    //转换为删除情景2.2.2.1
                    s = rotate_left(s); //rotate之后更新新的兄弟节点
                    //注意：这里要将新的s链接上p
                    p->left = s;
                }

                //删除情景2.2.2.1：替换结点的兄弟结点的左子结点是红结点，右子结点任意颜色
                s->color = p->color;
                p->color = BLACK;
                if (s->left != nullptr) {
                    s->left->color = BLACK;
                }
                p = rotate_right(p);
                //平衡indicator 清除
                balance_indicator = false;
                return p;
            }
        }
    }
}

//返回节点p的最左子树节点，用于找到后继节点
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

    int arr2[] = { 80, 10, 50, 40 };
    for (int i = 0; i < 4; i++) {
        tree.remove(arr2[i]);
        std::cout << "remove value: " << arr2[i] << " tree balance check : " << tree.is_balance() << std::endl;
    }
    std::cout << "After removed, tree is" << std::endl;
    tree.print();
    return 0;
}