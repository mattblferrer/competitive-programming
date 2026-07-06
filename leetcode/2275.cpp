class Solution {
public:
    int largestCombination(vector<int> &candidates) {
        map<int, int> bits;
        for (int i = 0; i < candidates.size(); i++) {
            for (int j = 0; j < 32; j++) {
                if (candidates[i] & (1 << j)) bits[j]++;
            }
        }
        int ans = 0;
        for (auto pair : bits) {
            ans = max(ans, pair.second);
        }
        return ans;
    }
};