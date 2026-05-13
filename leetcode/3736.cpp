#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMoves(vector<int>& nums) {
        int maxn = 0;
        for (int i = 0; i < nums.size(); i++) {
            maxn = max(maxn, nums[i]);
        }
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) ans += maxn - nums[i];
        return ans;
    }
};
