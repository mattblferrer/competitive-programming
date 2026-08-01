class Solution {
public:
    long long minInitialStrength(vector<int> &monsters, vector<vector<int>> &boosts) {
        int n = monsters.size(), m = boosts.size();
        vector<long long> diff(n + 1);
        for (int i = 0; i < m; i++) {
            long long li = boosts[i][0], ri = boosts[i][1], vi = boosts[i][2];
            diff[li] += vi;
            diff[ri + 1] -= vi;
        }
        vector<long long> temp_b(n);
        temp_b[0] = diff[0];
        for (int i = 1; i < n; i++) {
            temp_b[i] = temp_b[i - 1] + diff[i];
        }

        long long left = -1, right = 1'000'000'000'000'000;
        while (right - left > 1) {
            long long mid = midpoint(left, right), s = mid;
            bool possible = true;
            for (int i = 0; i < n; i++) {
                if (s + temp_b[i] >= monsters[i]) {
                    s = max(0LL, s - monsters[i]);
                }
                else { possible = false; break; }
            }
            if (possible) right = mid;
            else left = mid;
        }
        return right;
    }
};