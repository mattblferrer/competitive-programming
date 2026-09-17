class Solution {
public:
    inline static int pre = 0;
    inline static vector<int> evens = {0}, odds = {-1};
    void precompute() {
        if (pre) return;

        for (int i = 1; i < 100'000; i++) {
            string to_str = to_string(i);
            string rev(to_str.rbegin(), to_str.rend());

            if (i < 10'000) {
                string even_len = to_str + rev;
                int even_pal = stoi(even_len);
                if (even_pal % 2 == 0) evens.push_back(even_pal);
                else odds.push_back(even_pal);
            }
            string odd_len = to_str.substr(0, to_str.size() - 1) + rev;
            int odd_pal = stoi(odd_len);
            if (odd_pal % 2 == 0) evens.push_back(odd_pal);
            else odds.push_back(odd_pal);
        }
        sort(odds.begin(), odds.end());
        sort(evens.begin(), evens.end());

        pre = 1;
    }

    long long minOperations(vector<int> &nums) {
        precompute();

        int n = nums.size();
        long long ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            long long top, bottom;
            if (nums[i] % 2 == 0) {
                top = *lower_bound(evens.begin(), evens.end(), nums[i]);
                bottom = *prev(lower_bound(evens.begin(), evens.end(), nums[i]));
            }
            else {
                top = *lower_bound(odds.begin(), odds.end(), nums[i]);
                bottom = *prev(lower_bound(odds.begin(), odds.end(), nums[i]));
            }
            ans += min(abs(top - nums[i]) / 2, abs(nums[i] - bottom) / 2);
        }
        return ans;
    }
};