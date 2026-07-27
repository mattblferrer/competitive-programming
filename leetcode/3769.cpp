class Solution {
public:
    int rev_binary(int n) {
        string bin = "";
        while (n > 0) {
            if (n & 1) bin += '1';
            else bin += '0';
            n /= 2;
        }
        reverse(bin.begin(), bin.end());

        int ans = 0;
        while (bin.size()) {
            ans *= 2;
            ans += (bin.back() - '0');
            bin.pop_back();
        }
        return ans;
    }

    vector<int> sortByReflection(vector<int> &nums) {
        sort(nums.begin(), nums.end(), [this](int a, int b) {
            int ar = rev_binary(a), br = rev_binary(b);
            if (ar == br) return a < b;
            return ar < br;
            });
        return nums;
    }
};