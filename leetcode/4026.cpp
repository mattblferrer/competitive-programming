class Solution {
public:
    int maximumGap(string skill, string station) {
        int n = skill.size(), m = station.size();
        if (n == 1) return 0;

        int ans = 0;
        map<char, vector<int>> skill_mp, mp;
        map<char, int> index;
        for (int i = 0; i < n; i++) {
            skill_mp[skill[i]].push_back(i);
        }
        for (int i = 0; i < m; i++) {
            mp[station[i]].push_back(i);
        }

        vector<int> order(n);
        for (int i = 0; i < n; i++) {
            char c = skill[i];
            order[i] = mp[c][index[c]];
            index[c]++;
            if (i == 0) continue;

            while (order[i - 1] > order[i]) {
                order[i] = mp[c][index[c]];
                index[c]++;
            }
            ans = max(ans, order[i] - order[i - 1]);
        }

        index.clear();
        for (int i = n - 1; i >= 0; i--) {
            char c = skill[i];
            order[i] = mp[c][mp[c].size() - index[c] - 1];
            index[c]++;
            if (i == n - 1) {
                ans = max(ans, order[i] - order[i - 1]);
                continue;
            }

            while (order[i] > order[i + 1]) {
                order[i] = mp[c][mp[c].size() - index[c] - 1];
                index[c]++;
            }
            if (i != 0) ans = max(ans, order[i] - order[i - 1]);
        }

        return ans;
    }
};