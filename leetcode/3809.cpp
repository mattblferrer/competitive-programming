class Solution {
public:
    vector<int> bestTower(vector<vector<int>> &towers, vector<int> &center, int radius) {
        int cx = center[0], cy = center[1];
        long long max_q = -1;
        vector<int> ans = {-1, -1};
        for (int i = 0; i < towers.size(); i++) {
            int xi = towers[i][0], yi = towers[i][1];
            long long qi = towers[i][2];
            if (abs(xi - cx) + abs(yi - cy) > radius) continue;
            if (max_q < qi) {
                max_q = qi;
                ans = {xi, yi};
            }
            else if (max_q == qi) ans = min(ans, {xi, yi});
        }
        return ans;
    }
};