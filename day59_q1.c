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

// Global index for postorder
int postIndex;

// Build tree
struct TreeNode* build(int inorder[], int postorder[],
                       int inStart, int inEnd) {

    if (inStart > inEnd)
        return NULL;

    // Root from postorder
    int rootVal = postorder[postIndex--];
    struct TreeNode* root = newNode(rootVal);

    // Find root in inorder
    int inIndex = findIndex(inorder, inStart, inEnd, rootVal);

    // IMPORTANT: build right first
    root->right = build(inorder, postorder, inIndex + 1, inEnd);
    root->left  = build(inorder, postorder, inStart, inIndex - 1);

    return root;
}

// Preorder traversal
void preorder(struct TreeNode* root) {
    if (!root) return;

    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}

int main() {
    int n;
    scanf("%d", &n);

    int inorder[n], postorder[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &inorder[i]);

    for (int i = 0; i < n; i++)
        scanf("%d", &postorder[i]);

    postIndex = n - 1;

    struct TreeNode* root = build(inorder, postorder, 0, n - 1);

    preorder(root);

    return 0;
}
