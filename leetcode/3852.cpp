class Solution {
public:
    vector<int> minDistinctFreqPair(vector<int> &nums) {
        map<int, int> freq;
        for (int i = 0; i < nums.size(); i++) {
            freq[nums[i]]++;
        }
        for (auto pair : freq) {
            for (auto pair2 : freq) {
                if (pair.second != pair2.second) return {pair.first, pair2.first};
            }
        }
        return {-1, -1};
    }
};