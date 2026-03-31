#include <stdio.h>
#include <stdlib.h>

// Tree node
struct TreeNode {
    int val;
    struct TreeNode *left, *right;
};

// Create node
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

// Find index in inorder
int findIndex(int inorder[], int start, int end, int val) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == val)
            return i;
    }
    return -1;
}

// Build tree
struct TreeNode* build(int preorder[], int inorder[],
                       int preStart, int preEnd,
                       int inStart, int inEnd) {

    if (preStart > preEnd || inStart > inEnd)
        return NULL;

    // Root from preorder
    int rootVal = preorder[preStart];
    struct TreeNode* root = newNode(rootVal);

    // Find root in inorder
    int inIndex = findIndex(inorder, inStart, inEnd, rootVal);

    int leftSize = inIndex - inStart;

    // Left subtree
    root->left = build(preorder, inorder,
                       preStart + 1,
                       preStart + leftSize,
                       inStart,
                       inIndex - 1);

    // Right subtree
    root->right = build(preorder, inorder,
                        preStart + leftSize + 1,
                        preEnd,
                        inIndex + 1,
                        inEnd);

    return root;
}

// Postorder traversal
void postorder(struct TreeNode* root) {
    if (!root) return;

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->val);
}

int main() {
    int n;
    scanf("%d", &n);

    int preorder[n], inorder[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &preorder[i]);

    for (int i = 0; i < n; i++)
        scanf("%d", &inorder[i]);

    struct TreeNode* root = build(preorder, inorder,
                                  0, n - 1,
                                  0, n - 1);

    postorder(root);

    return 0;
}
