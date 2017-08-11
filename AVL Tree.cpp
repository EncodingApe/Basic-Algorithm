#include <iostream>
#include <algorithm>

using namespace std;

struct AVLTreeNode {
    int key;
    AVLTreeNode* lchild;
    AVLTreeNode* rchild;
    int height;
};

int height(AVLTreeNode* node) {
    return node == nullptr ? 0 : node->height;
}

AVLTreeNode* left_left_rotate(AVLTreeNode* root) {
    int lheight, rheight;
    AVLTreeNode *r1, *r2 = root;
    r1 = root->lchild;
    r2->lchild = r1->rchild;
    r1->rchild = r2;

    lheight = height(r2->lchild);
    rheight = height(r2->rchild);
    r2->height = max(lheight, rheight) + 1;

    lheight = height(r1->lchild);
    rheight = height(r1->rchild);
    r1->height = max(lheight, rheight) + 1;

    return r1;
}

AVLTreeNode* right_right_rotate(AVLTreeNode* root) {
    int lheight, rheight;
    AVLTreeNode *r1, *r2 = root;
    r1 = r2->rchild;
    r2->rchild = r1->lchild;
    r1->lchild = r2;

    lheight = height(r2->lchild);
    rheight = height(r2->rchild);
    r2->height = max(lheight, rheight) + 1;

    lheight = height(r1->lchild);
    rheight = height(r1->rchild);
    r1->height = max(lheight, rheight) + 1;

    return r1;
}

AVLTreeNode* insert(AVLTreeNode* root, int key) {
    int lheight, rheight;
    if(root == nullptr) {
        AVLTreeNode* node = new AVLTreeNode();
        node->key = key;
        node->rchild = node->lchild = nullptr;
        node->height = 1;
        return node;
    } else if(key < root->key) {
        root->lchild = insert(root->lchild, key);

        lheight = height(root->lchild);
        rheight = height(root->rchild);
        root->height = max(lheight, rheight) + 1;
    } else if(key > root->key) {
        root->rchild = insert(root->rchild, key);

        lheight = height(root->lchild);
        rheight = height(root->rchild);
        root->height = max(lheight, rheight) + 1;
    }

    if(height(root->lchild) - height(root->rchild) == 2) {  // 多出来的一个节点出现在了根的左子树上 可能是LL或LR情况
        if(key < root->lchild->key) {   // 多出来的节点出现在了根的左子树的左子树上 是LL情况 进行LL旋转
            root = left_left_rotate(root);
        } else if(key > root->lchild->key) {    // 多出来的节点出现在了根的左子树的右子树上 是LR情况
            root->lchild = right_right_rotate(root->lchild);    // 先对左子树进行RR旋转
            root = left_left_rotate(root);  // 再对整个树进行LL旋转
        }
    } else if(height(root->rchild) - height(root->lchild) == 2) {
        if(key < root->rchild->key) {
            root->rchild = left_left_rotate(root->rchild);  // 先对右子树进行LL旋转
            root = right_right_rotate(root);    // 再对整棵树进行RR旋转
        } else if(key > root->rchild->key) {
            root = right_right_rotate(root);
        }
    }
    return root;
}

int main(int argc, char const *argv[]) {
    int n;
    scanf("%d", &n);

    // 初始化树根
    AVLTreeNode* root = nullptr;

    int tmp;
    for(int i=0; i<n; i++) {
        scanf("%d", &tmp);
        root = insert(root, tmp);
    }
    cout << root->key;
    return 0;
}
