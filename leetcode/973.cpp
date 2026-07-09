class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>> &points, int k) {
        vector<vector<int>> sorted(points.begin(), points.end());
        sort(sorted.begin(), sorted.end(), [](vector<int> a, vector<int> b) {
            return (a[0] * a[0] + a[1] * a[1]) < (b[0] * b[0] + b[1] * b[1]);
            });
        vector<vector<int>> ans(sorted.begin(), sorted.begin() + k);
        return ans;
    }
};