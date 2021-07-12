//平衡二叉搜索树(AVL tree，Adelson-Velsky and Landis Tree, 简称平衡二叉树)
//性质：每个节点的左子树和右子树的高度差至多为1
//时间复杂度等同二叉搜索树，且稳定为O(logn)

#ifndef _AVL_TREE_IMPROVE_H_
#define _AVL_TREE_IMPROVE_H_

//Node结构
template <class K, class V>
class Node {
public:
    K key;
    V value;
    Node<K, V>* left;
    Node<K, V>* right;
    Node(K key_, V value_)
    {
        key = key_;
        value = value_;
        left = nullptr;
        right = nullptr;
    }
};

//AVL tree 结构
template <class K, class V>
class AVLTree {
public:
    AVLTree()
    {
        root = nullptr;
    }

    //基本接口
    void insert(K key, V value);
    Node<K, V>* find(K key);
    void remove(K key);

    //测试接口
    bool is_balance();
    void print();

private:
    Node<K, V>* root;

    /*********************
     **    四种旋转方式   **
     **********************/

    //LL平衡旋转 (向右单旋转)：在左孩子(L)的左子树(L)插入导致的不平衡
    Node<K, V>* LL_rotate(Node<K, V>* p);

    //RR平衡旋转 (向左单旋转)：在右孩子(R)的右子树(R)插入导致的不平衡
    Node<K, V>* RR_rotate(Node<K, V>* p);

    //RL平衡旋转 (先向右后向左双旋转)：在右孩子(R)的左子树(L)插入导致的不平衡
    Node<K, V>* RL_rotate(Node<K, V>* p);

    //LR平衡旋转 (先向左后向右双旋转)：在左孩子(L)的右子树(R)插入导致的不平衡
    Node<K, V>* LR_rotate(Node<K, V>* p);

    //获取高度
    int get_height(Node<K, V>* p);

    //获取节点的平衡因子
    int get_balance_factor(Node<K, V>* p);

    //平衡节点 (平衡二叉树的关键)
    Node<K, V>* balance(Node<K, V>* p);

    //插入，查找，删除
    Node<K, V>* insert(Node<K, V>* p, K key, V value);
    Node<K, V>* find(Node<K, V>* p, K key);
    Node<K, V>* remove(Node<K, V>* p, K key);

    //返回最大节点和最小节点，用于找前继节点和后继节点
    Node<K, V>* find_max(Node<K, V>* p);
    Node<K, V>* find_min(Node<K, V>* p);

    //遍历
    void pre_order_traverse(Node<K, V>* p);
    void mid_order_traverse(Node<K, V>* p);

    bool is_balance(Node<K, V>* p);
};

#endif