class Solution {
public:
    vector<vector<int>> mergeArrays(vector<vector<int>> &nums1, vector<vector<int>> &nums2) {
        map<int, int> merge;
        for (int i = 0; i < nums1.size(); i++) merge[nums1[i][0]] += nums1[i][1];
        for (int i = 0; i < nums2.size(); i++) merge[nums2[i][0]] += nums2[i][1];
        vector<vector<int>> ans;
        for (auto pair : merge) ans.push_back({pair.first, pair.second});
        return ans;
    }
};