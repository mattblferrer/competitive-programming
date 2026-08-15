class Solution {
public:
    vector<vector<int>> mergeSimilarItems(vector<vector<int>> &items1, vector<vector<int>> &items2) {
        map<int, int> mp;
        for (auto &vec : items1) mp[vec[0]] += vec[1];
        for (auto &vec : items2) mp[vec[0]] += vec[1];
        vector<vector<int>> ans;
        for (auto &pair : mp) ans.push_back({pair.first, pair.second});
        return ans;
    }
};