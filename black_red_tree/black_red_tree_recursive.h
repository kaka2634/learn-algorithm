//红黑树
//参考： https://www.jianshu.com/p/e136ec79235c

#ifndef _BLACK_RED_TREE_H_
#define _BLACK_RED_TREE_H_

enum COLOR { RED,
    BLACK };

//节点结构
template <class K, class V>
class Node {
public:
    K key;
    V value;
    Node<K, V>* left;
    Node<K, V>* right;
    COLOR color;
    Node(K key_, V value_, COLOR color_)
    {
        key = key_;
        value = value_;
        left = nullptr;
        right = nullptr;
        color = color_;
    }
};

template <class K, class V>
class BRTree {
public:
    BRTree()
    {
        root = nullptr;
    }

    //基本接口
    void insert(K key, V value);
    Node<K, V>* find(K key);
    void remove(K key);

    //测试接口
    void print();
    bool is_balance();

private:
    Node<K, V>* root;

    //旋转操作
    Node<K, V>* rotate_left(Node<K, V>* p);
    Node<K, V>* rotate_right(Node<K, V>* p);

    //平衡操作
    Node<K, V>* insert_balance(Node<K, V>* pp, Node<K, V>* p, Node<K, V>* u);
    Node<K, V>* remove_balance(Node<K, V>* p, Node<K, V>* s, bool& balance_indicator);

    //插入
    Node<K, V>* insert(Node<K, V>* p, K key, V value);
    //查找
    Node<K, V>* find(Node<K, V>* p, K key);
    //删除
    Node<K, V>* remove(Node<K, V>* p, K key, bool& balance_indicator);
    //寻找子树最小节点
    Node<K, V>* find_min(Node<K, V>* p);

    //遍历
    void pre_order_traverse(Node<K, V>* p);
    void mid_order_traverse(Node<K, V>* p);

    bool is_balance(Node<K, V>* p, Node<K, V>* c, int cur_black_num, int target_black_num);
};

#endif