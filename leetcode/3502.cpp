class Solution {
public:
    vector<int> minCosts(vector<int> &cost) {
        int n = cost.size();
        vector<int> ans(n);
        int curr = 1'000'000;
        for (int i = 0; i < n; i++) {
            curr = min(curr, cost[i]);
            ans[i] = curr;
        }
        return ans;
    }
};