#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numSquares(int n) {
        vector<int> sq;
        for (int i = 0; i <= 100; i++) sq.push_back(i * i);
        vector<int> dp(n + 1, 1000000);
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= 100; j++) {
                if (sq[j] > i) break;
                dp[i] = min(dp[i], 1 + dp[i - sq[j]]);
            }
        }
        return dp[n];
    }
};