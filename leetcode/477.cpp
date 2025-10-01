#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int ans = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                ans += __builtin_popcount(nums[i] ^ nums[j]);
            }
        }

        return ans;
    }
};