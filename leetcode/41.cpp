#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        vector<int> cnt(n + 1);
        for (int i = 0; i < n; i++) {
            if (nums[i] >= 0 && nums[i] <= n) cnt[nums[i]]++;
        }
        for (int i = 1; i <= n; i++) {
            if (cnt[i] == 0) return i; 
        }
        return n + 1;
    }
};