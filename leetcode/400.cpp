class Solution {
public:
    int findNthDigit(int n) {
        if (n < 10) return n;

        vector<long long> block_div = {0}, pows10 = {1};
        long long div = 1, dig = 1, pow = 1;
        while (div <= n) {
            div += dig * pow * 9;
            block_div.push_back(div);
            dig++;
            pow *= 10;
            pows10.push_back(pow);
        }
        long long curr_pow = 0;
        for (int i = 0; i < block_div.size(); i++) {
            if (block_div[i] >= n) {
                curr_pow = i - 1;
                break;
            }
        }
        long long curr_idx = pows10[curr_pow] + (n - block_div[curr_pow]) / (curr_pow + 1);
        long long curr_dig = (n - block_div[curr_pow]) % (curr_pow + 1);
        long long ans = to_string(curr_idx)[curr_dig] - '0';
        return ans;
    }
};