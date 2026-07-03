class Solution {
public:
    int minOperations(vector<int> &nums, int k) {
        int min_n = *min_element(nums.begin(), nums.end());
        if (min_n < k) return -1;
        sort(nums.begin(), nums.end());
        set<int> unique;
        for (int i = 0; i < nums.size(); i++) unique.insert(nums[i]);
        if (min_n == k) return unique.size() - 1;
        else return unique.size();
    }
};