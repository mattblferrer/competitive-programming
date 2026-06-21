class Solution {
public:
    int maxIceCream(vector<int> &costs, int coins) {
        int m = *max_element(costs.begin(), costs.end());
        vector<int> cnt(m + 1);
        int n = costs.size();
        for (int i = 0; i < n; i++) cnt[costs[i]]++;
        vector<int> pref(m + 1);
        for (int i = 1; i < m + 1; i++) pref[i] = pref[i - 1] + cnt[i];
        vector<int> sorted(n);
        for (int i = 0; i < n; i++) {
            sorted[pref[costs[i]] - 1] = costs[i];
            pref[costs[i]]--;
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (coins < sorted[i]) break;
            coins -= sorted[i];
            ans++;
        }

        return ans;
    }
};