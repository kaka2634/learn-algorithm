#include "avl_tree.h"
#include <iostream>
using namespace std;

//LL平衡旋转 (向右单旋转)
//假定根节点为A，左孩子为B, 因为左孩子B的左子树BL插入节点导致了不平衡
Node* AVLTree::LL_rotate(Node* root)
{
    //1.先记录左孩子B到temp
    Node* temp = root->left;
    //2. 将左孩子B的右子树BR 连接 成为节点A的左子树AL
    root->left = temp->right;
    //3. 将左孩子B的右孩子更换成为节点A -> 左孩子B向右实现了旋转
    temp->right = root;
    //4. 返回左孩子B作为根节点
    return temp;
}

//RR平衡旋转 (向左单旋转) -> 是向右旋转的镜像
//假定根节点为A，右孩子为B, 因为右孩子B的右子树BR插入节点导致了不平衡
Node* AVLTree::RR_rotate(Node* root)
{
    //1.先记录右孩子B到temp
    Node* temp = root->right;
    //2. 将右孩子B的左子树BL 连接 成为节点A的右子树AR
    root->right = temp->left;
    //3. 将右孩子B的左孩子更换成为节点A -> 右孩子B向左实现了旋转
    temp->left = root;
    //4. 返回右孩子B作为根节点
    return temp;
}

//RL平衡旋转 (先向右后向左双旋转)
//假定根节点为A，右孩子为B, 因为右孩子B的左孩子C的子树CL/CR插入节点导致了不平衡
Node* AVLTree::RL_rotate(Node* root)
{
    //1. 先对右孩子B使用LL_rotate, 向右旋转将左孩子C提上来，A的右孩子将从B变为C
    root->right = LL_rotate(root->right);
    //2. 再对根节点A使用RR_rotate, 向左旋转将此时根节点A的右孩子C提上来
    return RR_rotate(root);
}

//LR平衡旋转 (先向左后向右双旋转)
//假定根节点为A，左孩子为B, 因为左孩子B的右孩子的子树CL/CR插入节点导致了不平衡
Node* AVLTree::LR_rotate(Node* root)
{
    //1. 先对左孩子B使用RR_rotate, 向左旋转将右孩子C提上来，A的左孩子将从B变为C
    root->left = RR_rotate(root->left);
    //2. 再对根节点A使用LL_rotate, 向右旋转将此时根节点A的左孩子C提上来
    return LL_rotate(root);
}

//获取节点的高度 -> 递归
int AVLTree::get_height(Node* p)
{
    if (p == nullptr)
        return 0;
    int left = get_height(p->left);
    int right = get_height(p->right);
    return left > right ? left + 1 : right + 1;
}

//获取节点的平衡因子
int AVLTree::get_balance_factor(Node* p)
{
    return get_height(p->left) - get_height(p->right);
}

//平衡节点
//先看左子树还是右子树，再看是子树的左孩子还是右孩子，决定采用哪种旋转操作
Node* AVLTree::balance(Node* root)
{
    //获取根节点的平衡因子
    int root_factor = get_balance_factor(root);

    //1. 如果左子树树高更高
    if (root_factor > 1) {
        //获取左子树的平衡因子
        int child_factor = get_balance_factor(root->left);
        //child factor 与 0比较
        if (child_factor > 0) {
            //1.1 左子树(L)的左孩子(L)更高
            root = LL_rotate(root);

        } else {
            //1.2 左子树(L)的右孩子(R)更高
            root = LR_rotate(root);
        }
        //2. 如果右子树树高更高
    } else if (root_factor < -1) {
        //获取左子树的平衡因子
        int child_factor = get_balance_factor(root->right);
        //child factor 与 0比较
        if (child_factor > 0) {
            //2.1 右子树(R)的左孩子(L)更高
            root = RL_rotate(root);
        } else {
            //2.2 右子树(R)的右孩子(R)更高
            root = RR_rotate(root);
        }
    }
    //返回平衡后的根节点
    return root;
}

//返回二叉搜索树的最左节点，用于查找右子树中的后继节点（右子树中最小）
Node* AVLTree::find_min(Node* root)
{
    if (root == nullptr)
        return root;
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

//返回前最右节点，用于查找左子树中的前驱节点（左子树中最大）
Node* AVLTree::find_max(Node* root)
{
    if (root == nullptr)
        return root;
    while (root->right != nullptr) {
        root = root->right;
    }
    return root;
}

//插入
void AVLTree::insert(int x)
{
    tree_root = insert(tree_root, x);
}

//递归插入
Node* AVLTree::insert(Node* root, int x)
{
    //终结条件
    if (root == nullptr) {
        root = new Node(x);
        return root;
    }
    //左右子树判断
    if (root->val > x) {
        root->left = insert(root->left, x);
    } else {
        root->right = insert(root->right, x);
    }
    //相比二叉搜索树，唯一区别是在这里增加了平衡语句
    //平衡可能导致根节点变化，需要重新更新
    root = balance(root);
    return root;
}

void AVLTree::remove(int x)
{
    tree_root = remove(tree_root, x);
}

//递归删除
//重难点，比二叉搜索树删除，增加了左右子树高度判断和平衡过程
Node* AVLTree::remove(Node* root, int x)
{
    //终止条件1
    if (root == nullptr)
        return root;

    //终止条件2： 找到节点x
    if (root->val == x) {
        //1. 该节点左右子树均存在
        if (root->left && root->right) {
            int root_factor = get_balance_factor(root);
            if (root_factor > 0) {
                //1.1 左子树更高,则将根节点的值更换为左子树中最大的节点的值
                Node* temp = find_max(root->left);
                root->val = temp->val;
                //再递归调用删除掉左子树中最大的节点 (可在二叉搜索树使用该方法，更清楚)
                //因为左子树最大的节点将不会有右孩子，所以只会进入条件2
                //同时会继续递归调用平衡操作方法
                root->left = remove(root->left, temp->val);
            } else {
                //1.1 右子树更高,则将根节点的值更换为右子树中最小的节点的值
                Node* temp = find_min(root->right);
                root->val = temp->val;
                root->right = remove(root->right, temp->val);
            }
        } else {
            //2. 该节点只会存在至多一个子树
            //直接将子树的孩子节点提为根节点
            Node* temp = root;
            if (root->right == nullptr) {
                root = root->left;
            } else {
                root = root->right;
            }
            delete temp;
            temp = nullptr;
        }
    } else if (root->val > x) {
        //继续在左子树搜索
        root->left = remove(root->left, x);
        //如果删除可能造成不平衡，需要进行平衡操作
        root = balance(root);
    } else {
        //继续在右子树搜索
        root->right = remove(root->right, x);
        root = balance(root);
    }
    //返回根节点
    return root;
}

Node* AVLTree::find(int x)
{
    return find(tree_root, x);
}

//递归查找
Node* AVLTree::find(Node* root, int x)
{
    if (root == nullptr || root->val == x)
        return root;
    if (root->val > x)
        return find(root->left, x);
    return find(root->right, x);
}

void AVLTree::build(int arr[], int size)
{
    for (int i = 0; i < size; i++) {
        insert(arr[i]);
    }
}

void AVLTree::pre_order_traverse()
{
    cout << "pre order: ";
    pre_order_traverse(tree_root);
}

void AVLTree::pre_order_traverse(Node* root)
{
    if (root == nullptr)
        return;
    pre_order_traverse(root->left);
    cout << root->val << " ";
    pre_order_traverse(root->right);
}

void AVLTree::mid_order_traverse()
{
    cout << "mid orde: ";
    mid_order_traverse(tree_root);
}

void AVLTree::mid_order_traverse(Node* root)
{
    if (root == nullptr)
        return;
    cout << root->val << " ";
    mid_order_traverse(root->left);
    mid_order_traverse(root->right);
}

void AVLTree::print()
{
    pre_order_traverse();
    cout << endl;
    mid_order_traverse();
    cout << endl;
}

int main()
{
    int arr[] = { 8, 3, 1, 4, 7, 5, 2, 6 };
    AVLTree avl;
    avl.build(arr, 8);
    avl.print();
    for (int i = 1; i < 9; i++) {
        avl.remove(i);
        avl.print();
    }
}