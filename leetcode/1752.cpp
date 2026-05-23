#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool check(vector<int>& nums) {
        int n = nums.size();
        for (int start = 0; start < n; start++) {
            bool valid = true;
            for (int i = start; i < start + n - 1; i++) {
                if (nums[i % n] > nums[(i + 1) % n]) {
                    valid = false;
                    break;
                }
            }
            if (valid) return true;
        }

        return false;
    }
};