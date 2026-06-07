#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumCost(vector<int>& cost) {
        int ans = 0;
        sort(cost.begin(), cost.end());
        int n = cost.size();
        for (int i = n % 3; i < n; i += 3) {
            ans += cost[i + 1] + cost[i + 2];
        }
        for (int i = 0; i < n % 3; i++) ans += cost[i];
        return ans;
    }
};