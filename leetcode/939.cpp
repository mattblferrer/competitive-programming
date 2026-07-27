class Solution {
public:
    int minAreaRect(vector<vector<int>> &points) {
        int n = points.size();
        set<vector<int>> pts_set(points.begin(), points.end());
        int ans = 1'000'000'000;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x1 = points[i][0];
                int x2 = points[j][0];
                int y1 = points[i][1];
                int y2 = points[j][1];

                if ((x1 == x2) || (y1 == y2)) continue;
                if (pts_set.count({x1, y2}) == 0) continue;
                if (pts_set.count({x2, y1}) == 0) continue;
                ans = min(ans, abs(x2 - x1) * abs(y2 - y1));
            }
        }
        if (ans == 1'000'000'000) return 0;
        return ans;
    }
};