#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minEnergy(int n, int brightness, vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;
        merged.push_back(intervals[0]);
        for (auto interval : intervals) {
            if (merged.back()[1] < interval[0]) {
                merged.push_back(interval);
            }
            else {
                merged.back()[1] = max(merged.back()[1], interval[1]);
            }
        }

        long long ans = 0;
        for (int i = 0; i < merged.size(); i++) {
            long long a = merged[i][0];
            long long b = merged[i][1];
            long long length = b - a + 1;
            ans += (brightness + 2) / 3 * length;
        }
        return ans;
    }
};