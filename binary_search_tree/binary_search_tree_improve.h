//二叉搜索树（BST Binary Search Tree）
//性质： 左子树节点都要小，右子树的节点都要大
//方法： 插入，查询，删除
//时间复杂度：O(logn)

//节点结构: 指针链接左右子树
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

template <class K, class V>
class BSTree {
public:
    BSTree();
    //基本操作
    void insert(K key, V value);
    Node<K, V>* find(K key);
    void remove(K key);

    //测试接口

private:
    //根节点
    Node<K, V> root;

    //递归实现基本操作
    Node<K, V>* insert(Node<K, V>* p, K key, V value);
    Node<K, V>* find(Node<K, V>* p, K key);
    Node<K, V>* remove(Node<K, V>* p, K key);

    //用于返回后继节点
    Node<K, V>* find_min(Node<K, V>* p);
};
