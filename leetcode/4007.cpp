class Solution {
public:
    int maximumWidth(vector<int> &planks) {
        unordered_map<int, int> cnt, combine;
        int n = planks.size();
        for (int i = 0; i < n; i++) {
            cnt[planks[i]]++;
        }
        for (auto it = cnt.begin(); it != cnt.end(); it = next(it)) {
            for (auto it2 = it; it2 != cnt.end(); it2 = next(it2)) {
                int u = it->first, cnt_u = it->second;
                int v = it2->first, cnt_v = it2->second;

                if (u == v) combine[u + v] += cnt_u / 2;
                else combine[u + v] += min(cnt_u, cnt_v);
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, cnt[planks[i]] + combine[planks[i]]);
            for (int j = i + 1; j < n; j++) {
                ans = max(ans, cnt[planks[i] + planks[j]] + combine[planks[i] + planks[j]]);
            }
        }
        return ans;
    }
};