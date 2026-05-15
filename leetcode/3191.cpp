#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int ans = 0;
        for (int i = 0; i < nums.size() - 2; i++) {
            if (nums[i] == 0) {
                ans++;
                for (int j = 0; j < 3; j++) nums[i + j] = 1 - nums[i + j];
            }
        }

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) return -1;
        }
        return ans;
    }
};