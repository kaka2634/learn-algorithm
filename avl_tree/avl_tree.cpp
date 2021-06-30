//平衡二叉搜索树(AVL tree，Adelson-Velsky and Landis Tree, 简称平衡二叉树)
//性质：每个节点的左子树和右子树的高度差至多为1
//时间复杂度等同二叉搜索树，且稳定为O(logn)
//参考： https://juejin.cn/post/6844904006033080333

//节点结构
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

//

class AVLTree {

private:
Node* root;

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



};


//LL平衡旋转 (向右单旋转)
//假定根节点为A，左孩子为B, 因为左孩子B的左子树BL插入节点导致了不平衡
Node* AVLTree::LL_rotate(Node* root) {
    //1.先记录左孩子B到temp
    Node* temp = root ->left;
    //2. 将左孩子B的右子树BR 连接 成为节点A的左子树AL
    root->left = temp ->right;
    //3. 将左孩子B的右孩子更换成为节点A -> 左孩子B向右实现了旋转
    temp->right = root;
    //4. 返回左孩子B作为根节点
    return temp;
}

//RR平衡旋转 (向左单旋转) -> 是向右旋转的镜像
//假定根节点为A，右孩子为B, 因为右孩子B的右子树BR插入节点导致了不平衡
Node* AVLTree::RR_rotate(Node* root) {
    //1.先记录右孩子B到temp
    Node* temp = root ->right;
    //2. 将右孩子B的左子树BL 连接 成为节点A的右子树AR
    root->right = temp ->left;
    //3. 将右孩子B的左孩子更换成为节点A -> 右孩子B向左实现了旋转
    temp->left = root;
    //4. 返回右孩子B作为根节点
    return temp;
}


//RL平衡旋转 (先向右后向左双旋转)
//假定根节点为A，右孩子为B, 因为右孩子B的左孩子C的子树CL/CR插入节点导致了不平衡
Node* AVLTree::RL_rotate(Node* root){
    //1. 先对右孩子B使用LL_rotate, 向右旋转将左孩子C提上来，A的右孩子将从B变为C
    root->right = LL_rotate(root->right);
    //2. 再对根节点A使用RR_rotate, 向左旋转将此时根节点A的右孩子C提上来
    return RR_rotate(root);
}

//LR平衡旋转 (先向左后向右双旋转)
//假定根节点为A，左孩子为B, 因为左孩子B的右孩子的子树CL/CR插入节点导致了不平衡
Node* AVLTree::LR_rotate(Node* root){
    //1. 先对左孩子B使用RR_rotate, 向左旋转将右孩子C提上来，A的左孩子将从B变为C
    root->left = RR_rotate(root->left);
    //2. 再对根节点A使用LL_rotate, 向右旋转将此时根节点A的左孩子C提上来
    return LL_rotate(root);
}