class Solution {
public:
    vector<vector<int>> ans;
    void helper(vector<int>& ar, int n, int k) {
        if (ar.size() == k) ans.push_back(ar);

        int start;
        if (ar.empty()) start = 1;
        else start = ar.back() + 1;
        for (int i = start; i <= n; i++) {
            ar.push_back(i);
            helper(ar, n, k);
            ar.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k) {
        vector<int> start;
        helper(start, n, k);
        return ans;
    }
};