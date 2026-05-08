#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> cnt(6003);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    int s = nums[i] + nums[j] + nums[k] + 3001;
                    cnt[s]++;
                }
            }
        }
        int ans = 0, min_diff = 100000;
        for (int i = 0; i < 6003; i++) {
            int diff = abs(target - (i - 3001));
            if ((cnt[i] > 0) && (diff < min_diff)) {
                min_diff = diff;
                ans = i - 3001;
            }
        }
        return ans;
    }
};