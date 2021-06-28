//二叉搜索树（BST Binary Search Tree）
//性质： 左子树节点都要小，右子树的节点都要大
//方法： 插入，查询，删除
//时间复杂度：O(logn)

//节点结构: 指针链接左右子树
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node(int x)
        : val(x)
        , left(nullptr)
        , right(nullptr) {};
};

//插入：递归版本
Node* insert(Node* p, int x)
{
    //递归终结条件
    if (p == nullptr) {
        //新建一个节点q返回
        Node* q = new Node(x);
        return q;
    }

    //二叉树分支选择递归
    if (x < p->val) {
        //选择左子树，同时连接插入节点
        p->left = insert(p->left, x);
    } else {
        //选择右子树，同时连接插入节点
        p->left = insert(p->right, x);
    }
    return p;
}

//查找：递归版本
Node* find(Node* p, int x)
{
    //递归终结条件: 找到节点x，或者到达nullptr
    if (p->val == x || p == nullptr) {
        return p;
    }

    //二叉树分支选择递归
    if (x < p->val) {
        //选择左子树
        return find(p->left, x);
    } else {
        //选择右子树
        return find(p->right, x);
    }
}

//删除： 递归版本
Node* remove(Node* p, int x)
{
    //终结条件1: 没有找到值为x的节点，返回
    if (p == nullptr) {
        return p;
    }

    //终结条件2： 找到节点x
    if (p->val == x) {
        //1. 如果删除的节点没有左儿子节点，那么将右儿子提上去
        if (p->left == nullptr) {
            Node* q = p->right;
            delete p;
            return q;
        }
        //2. 如果删除的节点左儿子没有右儿子节点，那么把左儿子提上去
        else if (p->left->right == nullptr) {
            Node* q = p->left;
            q->right = p->right;
            delete p;
            return q;
        }
        //3. 如果上面两个条件均不满足，就把左儿子节点子孙中最大的节点提上去
        else {
            Node* q;
            for (q = p->left; q->right->right != nullptr; q = q->right)
                ;
            Node* r = q->right;
            q->right = r->left;
            r->left = p->left;
            r->right = p->right;
            delete p;
            return r;
        }
    }

    //二叉树分支选择递归
    if (x < p->val) {
        //选择左子树，同时连接删除后的节点
        p->left = remove(p->left, x);
    } else {
        //选择右子树，同时连接删除后的节点
        p->right = remove(p->right, x);
    }
}