class Solution {
public:
    int countSpecialIntegers(vector<int> &nums) {
        map<int, vector<int>> idxs;
        for (int i = 0; i < nums.size(); i++) {
            idxs[nums[i]].push_back(i);
        }
        int ans = 0;
        for (auto &[n, vec] : idxs) {
            bool is_special = true;
            for (int i = 0; i < vec.size() - 1; i++) {
                if (vec[i] + 1 != vec[i + 1]) is_special = false;
            }
            if (is_special) ans++;
        }
        return ans;
    }
};