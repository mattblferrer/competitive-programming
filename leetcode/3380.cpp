class Solution {
public:
    int maxRectangleArea(vector<vector<int>> &points) {
        int n = points.size(), ans = -1;
        sort(points.begin(), points.end());
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    for (int l = k + 1; l < n; l++) {
                        int x1 = points[i][0], y1 = points[i][1];
                        int x2 = points[j][0], y2 = points[j][1];
                        int x3 = points[k][0], y3 = points[k][1];
                        int x4 = points[l][0], y4 = points[l][1];
                        if ((x1 != x2) || (x3 != x4)) continue;
                        if ((y1 != y3) || (y2 != y4)) continue;

                        bool contains = false;
                        for (int m = 0; m < n; m++) {
                            if ((m == i) || (m == j) || (m == k) || (m == l)) continue;
                            int xt = points[m][0], yt = points[m][1];

                            if ((x1 <= xt) && (xt <= x3) && (y1 <= yt) && (yt <= y2)) {
                                contains = true;
                                break;
                            }
                        }
                        if (!contains) ans = max(ans, abs(x3 - x1) * abs(y2 - y1));
                    }
                }
            }
        }
        return ans;
    }
};