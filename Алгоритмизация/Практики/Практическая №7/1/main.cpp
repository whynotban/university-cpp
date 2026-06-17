#include <iostream>
#include <algorithm>
#include <climits>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
    int maxSum;

    int maxGain(TreeNode* node) {
        if (node == nullptr) return 0;
        int leftGain = std::max(maxGain(node->left), 0);
        int rightGain = std::max(maxGain(node->right), 0);
        int priceNewPath = node->val + leftGain + rightGain;
        maxSum = std::max(maxSum, priceNewPath);
        return node->val + std::max(leftGain, rightGain);
    }

public:
    int maxPathSum(TreeNode* root) {
        maxSum = INT_MIN;
        maxGain(root);
        return maxSum;
    }
};

int main() {
    TreeNode* root = new TreeNode(-5);
    root->left = new TreeNode(1);
    root->right = new TreeNode(7);
    root->right->left = new TreeNode(2);
    root->right->right = new TreeNode(3);

    Solution sol;
    int result = sol.maxPathSum(root);
    std::cout << result << std::endl;

    return 0;
}
