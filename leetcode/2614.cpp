#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPrime(int n) {
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return n > 1;
    }

    int diagonalPrime(vector<vector<int>>& nums) {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if ((i == j) || (i == n - j - 1)) {
                    if (isPrime(nums[i][j])) {
                        ans = max(ans, nums[i][j]);
                    }
                }
            }
        }
        return ans;
    }
};