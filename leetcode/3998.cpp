class Solution {
public:
    vector<bool> transformStr(string s, vector<string> &strs) {
        int n = s.size();
        vector<int> s_cnt(2), z1;
        for (int i = 0; i < n; i++) {
            s_cnt[s[i] - '0']++;
            if (s[i] == '0') z1.push_back(i);
        }

        vector<int> str_cnt(2);
        vector<bool> ans(strs.size(), true);
        for (int i = 0; i < strs.size(); i++) {
            fill(str_cnt.begin(), str_cnt.end(), 0);
            for (int j = 0; j < n; j++) {
                if (strs[i][j] != '?') str_cnt[strs[i][j] - '0']++;
            }
            for (int j = 0; j < 2; j++) {
                if (str_cnt[j] > s_cnt[j]) ans[i] = false;
            }
            if (!ans[i]) continue;

            int need_0 = s_cnt[0] - str_cnt[0];
            int need_1 = s_cnt[1] - str_cnt[1];
            for (int j = 0; j < n; j++) {
                if (strs[i][j] == '?') {
                    if (need_0) {
                        strs[i][j] = '0';
                        need_0--;
                    }
                    else {
                        strs[i][j] = '1';
                        need_1--;
                    }
                }
            }

            vector<int> z2;
            for (int j = 0; j < n; j++) {
                if (strs[i][j] == '0') z2.push_back(j);
            }
            for (int j = 0; j < z2.size(); j++) {
                if (z1[j] < z2[j]) {
                    ans[i] = false;
                    break;
                }
            }
        }
        return ans;
    }
};