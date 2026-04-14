#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int INF = 100000000;
    int coinChange(vector<int>& coins, int amount) {
        vector<int> need(amount + 1, INF);
        need[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int c: coins) {
                if (c > i) continue;
                need[i] = min(need[i], need[i - c] + 1);
            }
        }
        if (need[amount] >= INF) return -1;
        return need[amount];
    }
};