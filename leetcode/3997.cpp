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
    int ans = 0;
    int traverse(TreeNode *root) {
        if (root == nullptr) return 0;
        int max_below = max(traverse(root->left), traverse(root->right));
        if (root->val >= max_below) ans++;
        return max({root->val, max_below});
    }
    int countDominantNodes(TreeNode *root) {
        traverse(root);
        return ans;
    }
};