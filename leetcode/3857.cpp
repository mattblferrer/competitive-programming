#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCost(int n) {
        vector<int> cost(n + 1, 1000000000);
        cost[1] = 0;
        for (int i = 2; i <= n; i++) {
            for (int a = 1; a < i; a++) {
                cost[i] = min(cost[i], a * (i - a) + cost[a] + cost[i - a]);
            }
        }
        return cost[n];
    }
};