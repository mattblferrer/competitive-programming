class Solution {
public:
    vector<vector<int>> largeGroupPositions(string s) {
        vector<vector<int>> ans;
        s += ' ';
        int curr = 1;
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == s[i - 1]) curr++;
            else {
                if (curr >= 3) ans.push_back({i - curr, i - 1});
                curr = 1;
            }
        }
        return ans;
    }
};