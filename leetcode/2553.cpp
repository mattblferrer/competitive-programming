#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans;
        for (int i = 0; i < n; i++) {
            vector<int> curr;
            while (nums[i] > 0) {
                curr.push_back(nums[i] % 10);
                nums[i] /= 10;
            }
            reverse(curr.begin(), curr.end());
            for (int j : curr) ans.push_back(j);
        }
        return ans;
    }
};