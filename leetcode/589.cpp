/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    vector<int> preorder(Node* root) {
        if (root == nullptr) return {};
        vector<int> ans = {root->val};
        for (auto child : root->children) {
            vector<int> c = preorder(child);
            ans.insert(ans.end(), c.begin(), c.end());
        }
        return ans;
    }
};