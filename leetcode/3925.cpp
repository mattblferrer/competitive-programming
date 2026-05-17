#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> concatWithReverse(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n * 2);
        for (int i = 0; i < n; i++) {
            ans[i] = ans[2 * n - i - 1] = nums[i];
        }
        return ans;
    }
};