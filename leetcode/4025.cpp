class Solution {
public:
    int minPenalty(int period, vector<int> &lights, vector<int> &arrivalTime) {
        int m = lights.size(), n = arrivalTime.size();
        sort(lights.begin(), lights.end());
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int r = arrivalTime[i] % period;
            if (r >= lights.back()) ans = max(ans, period - r);
        }
        return ans;
    }
};