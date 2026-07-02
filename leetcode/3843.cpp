class Solution {
public:
    int firstUniqueFreq(vector<int> &nums) {
        map<int, int> freq, freq2;
        for (int i = 0; i < nums.size(); i++) freq[nums[i]]++;
        for (auto pair : freq) {
            freq2[pair.second]++;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (freq2[freq[nums[i]]] == 1) return nums[i];
        }
        return -1;
    }
};