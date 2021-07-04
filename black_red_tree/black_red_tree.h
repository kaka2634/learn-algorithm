//红黑树
//参考： https://www.jianshu.com/p/e136ec79235c

#ifndef _BLACK_RED_TREE_H_
#define _BLACK_RED_TREE_H_

enum COLOR { RED,
    BLACK };

//树节点一般key和value相同，当然也可以保存为键值对
//节点结构这里将key和value区分
//因为红黑树主要应用场景的key和value不相同
template <class K, class V>
class Node {
public:
    K key;
    V value;
    Node* left;
    Node* right;
    Node* parent;
    COLOR color;
    Node(K key_, V value_, COLOR color_)
    {
        key = key_;
        value = value_;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        color = color;
    }
};

template <class K, class V>
class BRTree {
public:
    //基本接口
    Node<K, V>* find(K key);
    void insert(K key, V value);
    void remove(K key);

private:
    Node<K, V>* root;

    //旋转操作
    Node<K, V>* rotate_left(Node<K, V>* node);
    Node<K, V>* rotate_right(Node<K, V>* node);

    //变色
    void flip_colors(Node<K, V>* node);

    //平衡操作
    void insert_balance(Node<K, V>* node);
    void remove_balance(Node<K, V>* node);
};

#endif