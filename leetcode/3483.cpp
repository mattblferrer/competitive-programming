class Solution {
public:
    int totalNumbers(vector<int> &digits) {
        int ans = 0;
        vector<int> cnt(10);
        for (int i = 0; i < digits.size(); i++) cnt[digits[i]]++;
        for (int i = 100; i <= 999; i += 2) {
            string d = to_string(i);
            vector<int> curr_cnt(10);
            for (int j = 0; j < 3; j++) curr_cnt[d[j] - '0']++;

            bool valid = true;
            for (int j = 0; j < 10; j++) {
                if (curr_cnt[j] > cnt[j]) {
                    valid = false;
                    break;
                }
            }
            if (valid) ans++;
        }
        return ans;
    }
};