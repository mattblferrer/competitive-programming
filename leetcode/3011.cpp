#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int bit_count(int n) {
        int ans = 0;
        while (n > 0) {
            if (n & 1) ans++;
            n /= 2;
        }
        return ans;
    }

    bool canSortArray(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - 1; j++) {
                if ((nums[j] > nums[j + 1]) && (bit_count(nums[j]) == bit_count(nums[j + 1]))) {
                    int temp = nums[j];
                    nums[j] = nums[j + 1];
                    nums[j + 1] = temp;
                }
            }
        }
        for (int i = 0; i < n - 1; i++) {
            if (nums[i] > nums[i + 1]) return false;
        }
        return true;
    }
};