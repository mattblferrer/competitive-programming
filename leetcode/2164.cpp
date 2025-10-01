#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> sortEvenOdd(vector<int>& nums) {
        vector<int> nums_odd, nums_even;
        for (int i = 0; i < nums.size(); i++) {
            if (i % 2 == 0) nums_even.push_back(nums[i]);
            else nums_odd.push_back(nums[i]);
        }
        sort(nums_even.begin(), nums_even.end());
        sort(nums_odd.begin(), nums_odd.end(), greater<int>());
        vector<int> ans;
        for (int i = 0; i < nums.size(); i++) {
            if (i % 2 == 0) ans.push_back(nums_even[i / 2]);
            else ans.push_back(nums_odd[i / 2]);
        }
        return ans;
    }
};