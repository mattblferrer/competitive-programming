#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxTotal(vector<int>& nums, string s) {
        long long ans = 0;
        int n = nums.size();
        vector<int> zeros;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') zeros.push_back(i);
            ans += nums[i];
        }
        zeros.push_back(n);
        for (int i = 0; i < zeros.size() - 1; i++) {
            int min_n = 1000000;
            for (int j = zeros[i]; j < zeros[i + 1]; j++) {
                min_n = min(min_n, nums[j]);
            }
            ans -= min_n;
        }
        return ans;
    }
};