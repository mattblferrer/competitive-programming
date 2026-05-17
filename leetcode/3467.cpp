#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> transformArray(vector<int>& nums) {
        int evens = 0, odds = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] % 2 == 0) evens++;
            else odds++;
        }
        vector<int> ans(nums.size());
        for (int i = 0; i < evens; i++) ans[i] = 0;
        for (int i = evens; i < nums.size(); i++) ans[i] = 1;
        return ans;
    }
};