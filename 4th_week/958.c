/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int CountNodes(struct TreeNode* root) {
    // 计算树的节点数
    if (root == NULL) {
        return 0;
    }
    return 1 + CountNodes(root -> left) + CountNodes(root -> right); // 左子树节点数 + 右子树节点数 + 根节点
}

bool CheckBalance(struct TreeNode* node, int index, int count) {
    // 验证树是否为完全二叉树
    bool res;
    if (node == NULL) {
        return true;
    }
    if (index >= count) {
        // 如果index大于count，说明已经遍历完了所有节点，但还没有到达最后一个节点，说明不是完全二叉树
        return false;
    }
    // 验证左子树和右子树是否为完全二叉树
    res = CheckBalance(node -> left, 2 * index + 1, count) && CheckBalance(node -> right, 2 * index + 2, count);
    return res;
}

bool isCompleteTree(struct TreeNode* root) {
    int count = CountNodes(root);
    return CheckBalance(root, 0 ,count);
}