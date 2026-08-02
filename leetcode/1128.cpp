class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>> &dominoes) {
        map<pair<int, int>, int> cnt;
        for (auto d : dominoes) {
            int a = d[0], b = d[1];
            if (a > b) swap(a, b);
            cnt[{a, b}]++;
        }
        int ans = 0;
        for (auto pair : cnt) {
            ans += pair.second * (pair.second - 1) / 2;
        }
        return ans;
    }
};