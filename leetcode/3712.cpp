class Solution {
public:
    int sumDivisibleByK(vector<int> &nums, int k) {
        int ans = 0;
        map<int, int> freq;
        for (int i = 0; i < nums.size(); i++) freq[nums[i]]++;
        for (const auto &pair : freq) {
            if (pair.second % k == 0) ans += pair.first * pair.second;
        }
        return ans;
    }
};