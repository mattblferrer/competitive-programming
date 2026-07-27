class Solution {
public:
    vector<vector<int>> aggregateTimeSeries(vector<vector<int>> &series1, vector<vector<int>> &series2) {
        map<int, int> map1, map2, agg;
        int m = series1.size(), n = series2.size();
        for (int i = 0; i < m; i++) {
            map1[series1[i][0]] = series1[i][1];
        }
        for (int i = 0; i < n; i++) {
            map2[series2[i][0]] = series2[i][1];
        }
        for (int i = 0; i < m; i++) {
            auto it = map2.upper_bound(series1[i][0] - 1);
            if (it == map2.end()) agg[series1[i][0]] = series1[i][1];
            else agg[series1[i][0]] = series1[i][1] + it->second;
        }
        for (int i = 0; i < n; i++) {
            auto it = map1.upper_bound(series2[i][0] - 1);
            if (it == map1.end()) agg[series2[i][0]] = series2[i][1];
            else agg[series2[i][0]] = series2[i][1] + it->second;
        }
        vector<vector<int>> ans;
        for (const auto &pair : agg) {
            ans.push_back({pair.first, pair.second});
        }
        return ans;
    }
};