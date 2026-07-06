class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>> &intervals) {
        int n = intervals.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            bool valid = true;
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                int a = intervals[i][0], b = intervals[i][1];
                int c = intervals[j][0], d = intervals[j][1];
                if ((c <= a) && (b <= d)) valid = false;
            }
            if (valid) ans++;
        }
        return ans;
    }
};