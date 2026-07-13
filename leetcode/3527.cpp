class Solution {
public:
    string findCommonResponse(vector<vector<string>> &responses) {
        vector<set<string>> remove_dup(responses.size());
        for (int i = 0; i < responses.size(); i++) {
            for (int j = 0; j < responses[i].size(); j++) {
                remove_dup[i].insert(responses[i][j]);
            }
        }
        map<string, int> cnt;
        for (int i = 0; i < responses.size(); i++) {
            for (string s : remove_dup[i]) cnt[s]++;
        }
        string ans = "";
        int max_cnt = 0;
        for (const auto &pair : cnt) {
            if (pair.second > max_cnt) {
                ans = pair.first;
                max_cnt = pair.second;
            }
        }
        return ans;
    }
};