class Solution {
public:
    bool isMiddleElementUnique(vector<int> &nums) {
        map<int, int> freq;
        for (int i = 0; i < nums.size(); i++) freq[nums[i]]++;
        return (freq[nums[nums.size() / 2]] == 1);
    }
};