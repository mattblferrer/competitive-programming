class Solution {
public:
    int minRectanglesToCoverPoints(vector<vector<int>> &points, int w) {
        sort(points.begin(), points.end());
        int ans = 1, curr_x = points[0][0];
        for (auto pt : points) {
            if (pt[0] > curr_x + w) {
                ans++;
                curr_x = pt[0];
            }
        }
        return ans;
    }
};