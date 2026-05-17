#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> ans(n + 1);
        for (int i = 2; i <= n; i++) {
            ans[i] = min(ans[i - 2] + cost[i - 2], ans[i - 1] + cost[i - 1]);
        }
        return ans[n];
    }
};