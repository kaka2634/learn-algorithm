//平衡二叉搜索树(AVL tree，Adelson-Velsky and Landis Tree, 简称平衡二叉树)
//性质：每个节点的左子树和右子树的高度差至多为1
//时间复杂度等同二叉搜索树，且稳定为O(logn)
//参考： https://juejin.cn/post/6844904006033080333

#ifndef AVL_TREE_H_
#define AVL_TREE_H_

//Node结构
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr)
    {
    }
};


//AVL tree 结构
class AVLTree {
public:
    //基本接口
    int get_height(Node* p);
    Node* find(int x);
    void insert(int x);
    void remove(int x);

    //测试接口
    void build(int arr[], int size);
    void pre_order_traverse();
    void mid_order_traverse();
    void print();

private:
    Node* tree_root;

    /*********************
     **    四种旋转方式   **
     **********************/

    //LL平衡旋转 (向右单旋转)：在左孩子(L)的左子树(L)插入导致的不平衡
    Node* LL_rotate(Node* root);

    //RR平衡旋转 (向左单旋转)：在右孩子(R)的右子树(R)插入导致的不平衡
    Node* RR_rotate(Node* root);

    //RL平衡旋转 (先向右后向左双旋转)：在右孩子(R)的左子树(L)插入导致的不平衡
    Node* RL_rotate(Node* root);

    //LR平衡旋转 (先向左后向右双旋转)：在左孩子(L)的右子树(R)插入导致的不平衡
    Node* LR_rotate(Node* root);

    /*********************
     **     平衡操作      **
     **********************/

    //获取节点的平衡因子
    int get_balance_factor(Node* p);

    //平衡节点 (平衡二叉树的关键)
    Node* balance(Node* root);

    /*********************
     ** 插入，查找，删除  **
     **********************/

    //递归插入
    Node* insert(Node* root, int x);

    //递归删除
    Node* remove(Node* root, int x);

    //递归查找
    Node* find(Node* root, int x);

    //返回最大节点
    Node* find_max(Node* root);

    //返回最小节点
    Node* find_min(Node* root);

    /*********************
     **     遍历         **
     **********************/
    void pre_order_traverse(Node* root);
    void mid_order_traverse(Node* root);
};

#endif 