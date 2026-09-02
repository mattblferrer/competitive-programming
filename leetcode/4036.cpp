class Solution {
public:
    vector<string> largestString(vector<int> &nums) {
        vector<string> ans(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            string binary = "";
            while (nums[i] > 0) {
                if (nums[i] % 2 == 1) binary += '1';
                else binary += '0';
                nums[i] /= 2;
            }
            for (int j = 0; j < binary.size(); j++) {
                if (binary[j] == '1') {
                    if (j >= 26) {
                        for (int k = 0; k < (1 << (j - 25)); k++) {
                            ans[i] += 'z';
                        }
                    }
                    else ans[i] += 'a' + j;
                }
            }
            reverse(ans[i].begin(), ans[i].end());
        }
        return ans;
    }
};