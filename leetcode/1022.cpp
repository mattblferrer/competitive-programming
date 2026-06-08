/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int sum = 0;
    void traverse(TreeNode* root, int curr) {
        if (root == nullptr) return;
        if (root->left == nullptr && root->right == nullptr) {
            sum += curr * 2 + root->val;
            return;
        }
        traverse(root->left, curr * 2 + root->val);
        traverse(root->right, curr * 2 + root->val);
    }
    int sumRootToLeaf(TreeNode* root) {
        traverse(root, 0);
        return sum;
    }
};