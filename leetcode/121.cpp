class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int min_cost = INT_MAX, ans = 0;
        for (int i = 0; i < prices.size(); i++) {
            ans = max(ans, prices[i] - min_cost);
            min_cost = min(min_cost, prices[i]);
        }
        return ans;
    }
};