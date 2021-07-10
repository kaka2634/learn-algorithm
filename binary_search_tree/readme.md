# 二叉搜索树 Binary Search Tree

### 前言
前面介绍了 [二叉堆](../heap/readme.md) 实际上是一种特殊的完全二叉树，通过利用完全二叉树的特性，使用了数组结构实现了二叉树，并具基于堆有序的性质。那么基于二叉树还有什么其他的数据结构呢？

其实基于二叉的结构性质，很容易想到二分法。那么是不是能够实现一种数据结构，既能使用二叉树的结构来保存数据，同时又能达到对数级别的搜索复杂度呢？可以的，这就是二叉搜索树。

### 基本概念

**二叉搜索树(BST, Binary Search Tree)** 在二叉树的基础上，还要具有这条的重要性质：**对于任意节点，其左子树的节点的值都比该节点小， 而右子树的节点的值都比该节点大。**

方法： 插入，查询， 删除


时间复杂度为最佳情况是 O(log­n)，而最坏情况是 O(n)。

最坏情况原因：

其他自平衡搜索树：

### 实现

#### 节点结构

因为二叉树数据结构实际上是要保存数据，而值的比较大多情况是数据的key，所以这里节点结构中即存储了key，同时也保存了对应的真正的值value。

```
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
```
这里节点结构只包含了左右子树两个指针，这两个指针就足够使用递归方式实现二叉搜索树。因为在递归返回的时候，会再对父节点进行更新操作。

如果是使用迭代方式实现，则需要在遍历过程中记录父节点，可以通过增加一个局部parent指针方式，或者在节点结构中增加一个parent指针。如果在节点结构中增加一个parent指针，需要增加维护这个parent指针的成本，这时候在树结构改变时一定要加倍注意。

迭代的方式的代码可能没有递归方式的简洁，但可以作为后面的任务，考虑再实现一个迭代方式的一般二叉平衡搜索树。

### 插入

插入的位置是在叶子节点

```
template <class K, class V>
void BSTree<K, V>::insert(K key, V value)
{
    //注意： 这里要更新root节点
    root = insert(root, key, value);
}

template <class K, class V>
Node<K, V>* BSTree<K, V>::insert(Node<K, V>* p, K key, V value)
{
    //终结条件1: 到达null节点，需新建节点返回，完成插入
    if (p == nullptr) {
        p = new Node<K, V>(key, value);
        return p;
    }

    //终结条件2：如果key相同，那么只需更新value，这里等同update操作
    if (p->key == key) {
        p->value = value;
        return p;
    }

    //否则就需要继续寻找子树
    //注意： 这里使用的技巧，将递归返回的节点用于更新左右子树的值，从而实现递归构造树
    if (key < p->key) {
        p->left = insert(p->left, key, value);
    } else {
        p->right = insert(p->right, key, value);
    }
    return p;
}
```

### 查询

查询就是简单的二分遍历二叉树了。

```
template <class K, class V>
Node<K, V>* BSTree<K, V>::find(K key)
{
    return find(root, key);
}

template <class K, class V>
Node<K, V>* BSTree<K, V>::find(Node<K, V>* p, K key)
{
    //终结条件: 到达null节点，或者找到对应节点
    if (p == nullptr || p->key == key) {
        return p;
    }

    //根据二叉搜索树的性质继续寻找
    if (key < p->key) {
        return find(p->left, key);
    } else {
        return find(p->right, key);
    }
}
```

### 删除

删除的三种情况：
- 如果没有孩子节点，那么直接删除
- 如果只有左子树，或者右子树，那么直接删除该节点，将子树节点作为替代节点返回
- 如果既有左子树，又有右子树，那么可以找前驱节点/后继节点作为替代节点，替换将要删除的节点，那么之后再删除掉替换节点就可以了

1. 删除其实也是要删除叶子节点。所以需要找替换节点。（对于情况2，实际上可以不断向上替代，找到到叶子节点再删除，但这里实际上不需要，但对其他自平衡二叉搜索树可能需要）
2. 前驱节点/后继节点 概念

找寻后继节点，通过传入右子树指针(pp->right)
```
//返回节点p的最左子树节点
template <class K, class V>
Node<K, V>* BSTree<K, V>::find_min(Node<K, V>* p)
{
    if (p == nullptr)
        return p;
    while (p->left != nullptr) {
        p = p->left;
    }
    return p;
}
```

删除
```
template <class K, class V>
void BSTree<K, V>::remove(K key)
{
    //注意： 这里要更新root节点
    root = remove(root, key);
}

template <class K, class V>
Node<K, V>* BSTree<K, V>::remove(Node<K, V>* p, K key)
{
    //终结条件1: 到达null节点，仍然没能找到，返回nullptr
    if (p == nullptr) {
        return p;
    }

    //终结条件2： 找到删除节点
    if (p->key == key) {
        //1. 如果没有左右孩子，直接删除该节点
        if (p->left == nullptr && p->right == nullptr) {
            delete p;
            p = nullptr;
            return p;
        }
        //2. 如果只有一个孩子，那么直接将孩子节点作为替换节点, 同时删除节点
        // 因为前面已经判断了两个都是nullptr的情况，这里只需判断一个孩子即可
        if (p->left == nullptr) {
            Node<K, V>* replace = p->right;
            delete p;
            p = nullptr;
            return replace;
        } else if (p->right == nullptr) {
            Node<K, V>* replace = p->left;
            delete p;
            p = nullptr;
            return replace;
        }

        //3. 剩下就是左右孩子都存在的情况，这里可以寻找后继节点作为替换节点（也可以使用前驱节点）
        Node<K, V>* replace = find_min(p->right);
        p->key = replace->key;
        p->value = replace->value;
        //注意：这里使用的树节点删除技巧，删除节点需要找到一个替代节点，将替代节点放到删除节点位置从而不会破坏树的性质。
        //再继续调用同样删除操作去将替换节点删除（更换key值），直到整个树在删除节点后满足基本性质。
        if (key > replace->key) {
            //key 比 replace 大，说明替换节点在左子树， 这与搜索条件刚好不同， 因为这里搜索的实际是replace->key, key表示的是p->key
            p->left = remove(p->left, replace->key);
        } else {
            p->right = remove(p->right, replace->key);
        }
    }
    //注意： 这里需要用else if，因为key的值可能会在前面替换节点时被修改了
    //同时，递归删除树同样需要将返回值用于更新左右子树指针
    else if (key < p->key) {
        p->left = remove(p->left, key);
    } else {
        p->right = remove(p->right, key);
    }
    return p;
}
```


