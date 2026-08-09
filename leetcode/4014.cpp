class Solution {
public:
    double minPrice(vector<int> &prices, vector<int> &discounts) {
        sort(prices.begin(), prices.end(), greater<int>());
        sort(discounts.begin(), discounts.end(), greater<int>());
        int m = prices.size(), n = discounts.size();
        double ans = 0;
        for (int i = 0; i < min(m, n); i++) {
            ans += ((double)prices[i] * (100 - discounts[i])) / 100;
        }
        for (int i = n; i < m; i++) {
            ans += prices[i];
        }
        return ans;
    }
};