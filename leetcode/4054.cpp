class Solution {
public:
    long long shadowPairs(vector<int> &nums) {
        int n = nums.size();
        long long ans = 0;
        vector<int> vec;
        map<int, int> cnt;

        for (int i = 0; i < n; i++) {
            while (!vec.empty() && vec.back() > nums[i]) {
                cnt[vec.back()]--;
                vec.pop_back();
            }
            ans += vec.size() - cnt[nums[i]];
            vec.push_back(nums[i]);
            cnt[nums[i]]++;
        }
        return ans;
    }
};