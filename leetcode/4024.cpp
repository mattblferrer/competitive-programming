class Solution {
public:
    int nearestDrone(vector<vector<int>> &drones, vector<int> &target) {
        int min_dist = 1'000'000, ans = -1, tx = target[0], ty = target[1];
        for (int i = 0; i < drones.size(); i++) {
            int xi = drones[i][0], yi = drones[i][1], range = drones[i][2];
            int dist = abs(xi - tx) + abs(yi - ty);
            if (range < dist) continue;
            if (min_dist > dist) {
                min_dist = dist;
                ans = i;
            }
        }
        return ans;
    }
};