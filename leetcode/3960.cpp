class Solution {
public:
    int getLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            map<int, int> freq;
            int max_freq = 0;

            for (int j = i; j < n; j++) {
                freq[nums[j]]++;
                max_freq = max(max_freq, freq[nums[j]]);
                if (freq.size() == 1) ans = max(ans, j - i + 1);
                if (j - i + 1 < ans) continue;
                if (max_freq % 2 != 0) continue;

                bool found_1 = false, found_2 = false, valid = true;
                for (const auto& pair : freq) {
                    if (pair.second == max_freq) found_1 = true;
                    else if (pair.second == max_freq / 2) found_2 = true;
                    else valid = false;
                }
                if (!(found_1 && found_2)) continue;
                if (valid) ans = max(ans, j - i + 1);
            }
        }
        return ans;
    }
}
