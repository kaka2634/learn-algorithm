//自平衡二叉搜索树(AVL tree，Adelson-Velsky and Landis Tree)
//性质：每个节点的左子树和右子树的高度差至多为1
//时间复杂度等同二叉搜索树，且稳定为O(logn)

//节点结构
class AVLNode {
public:
    int val;
    AVLNode* left;
    AVLNode* right;
    AVLNode(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr)
    {
    }
};