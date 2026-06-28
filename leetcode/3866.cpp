class Solution {
public:
    int firstUniqueEven(vector<int> &nums) {
        map<int, int> cnt;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] % 2 == 1) continue;
            cnt[nums[i]]++;
        }
        set<int> unique;
        for (auto pair : cnt) {
            if (pair.second > 1) continue;
            unique.insert(pair.first);
        }
        for (int i = 0; i < n; i++) {
            if (unique.count(nums[i])) return nums[i];
        }
        return -1;
    }
};