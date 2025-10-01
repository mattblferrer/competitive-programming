#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        vector<int> even, odd, ans;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] % 2 == 0) even.push_back(nums[i]);
            else odd.push_back(nums[i]);
        }
        for (int i = 0; i < nums.size(); i++) {
            if (i % 2 == 0) ans.push_back(even[i / 2]);
            else ans.push_back(odd[i / 2]);
        }
        return ans;
    }
};