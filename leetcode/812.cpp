class Solution {
public:
    double get_area(vector<int> &a, vector<int> &b, vector<int> &c) {
        double ab = sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
        double bc = sqrt(pow(b[0] - c[0], 2) + pow(b[1] - c[1], 2));
        double ca = sqrt(pow(c[0] - a[0], 2) + pow(c[1] - a[1], 2));
        double s = (ab + bc + ca) / 2;
        double area = sqrt(s * (s - ab) * (s - bc) * (s - ca));
        return area;
    }

    double largestTriangleArea(vector<vector<int>> &points) {
        int n = points.size();
        double ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    ans = max(ans, get_area(points[i], points[j], points[k]));
                }
            }
        }
        return ans;
    }
};