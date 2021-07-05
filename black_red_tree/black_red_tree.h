//红黑树
//参考： https://www.jianshu.com/p/e136ec79235c

#ifndef _BLACK_RED_TREE_H_
#define _BLACK_RED_TREE_H_

enum COLOR { RED,
    BLACK };

//树节点一般key和value相同，当然也可以保存为键值对
//节点结构这里将key和value区分
//因为红黑树主要应用场景的key和value不相同

//K key-type, V value-type
template <class K, class V>
class Node {
public:
    K key;
    V value;
    Node<K, V>* left;
    Node<K, V>* right;
    Node<K, V>* parent;
    COLOR color;
    Node(K key_, V value_, COLOR color_, Node<K, V>* parent_ = nullptr)
    {
        key = key_;
        value = value_;
        left = nullptr;
        right = nullptr;
        parent = parent_;
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
    Node<K, V>* find(K key);
    void insert(K key, V value);
    void remove(K key);

    //测试接口
    void pre_order_traverse();
    void mid_order_traverse();
    void print();
    bool is_balance();

private:
    Node<K, V>* root;

    //旋转操作
    Node<K, V>* rotate_left(Node<K, V>* p);
    Node<K, V>* rotate_right(Node<K, V>* p);

    //变色
    void flip_colors(Node<K, V>* p);

    //平衡操作
    void insert_balance(Node<K, V>* s);
    void remove_balance(Node<K, V>* s);

    //查找操作
    Node<K, V>* find_min(Node<K, V>* p);

    //遍历
    void pre_order_traverse(Node<K, V>* p);
    void mid_order_traverse(Node<K, V>* p);
    bool is_balance(Node<K, V>* p, int cur_black_num, int target_black_num);
};

#endif