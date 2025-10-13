bool isValidBST(TreeNode* root) {
    if (root == nullptr) {
        return true;
    }
    if (root->left != nullptr) {
        if (!isValidBST(root->left) || getMax(root->left) > root->val) {
            return false;
        }
    }
    if (root->right != nullptr) {
        if (!isValidBST(root->right) || getMin(root->right) < root->val) {
            return false;
        }
    }
    return true;
}

int getMin(TreeNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node->val;
}

int getMax(TreeNode* node) {
    while (node->right != nullptr) {
        node = node->right;
    }
    return node->val;
}