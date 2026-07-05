class Solution {
public:
    int maxDigitRange(vector<int> &nums) {
        map<int, int> digit_range;
        for (int i = 0; i < nums.size(); i++) {
            string to_str = to_string(nums[i]);
            int max_d = -1, min_d = 10;
            for (int j = 0; j < to_str.size(); j++) {
                max_d = max(max_d, to_str[j] - '0');
                min_d = min(min_d, to_str[j] - '0');
            }
            digit_range[max_d - min_d] += nums[i];
        }
        return digit_range.rbegin()->second;
    }
};