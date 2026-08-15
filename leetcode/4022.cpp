class Solution {
public:
    int kthDigit(long long k) {
        if (k < 10) return k;

        vector<long long> block_div = {0}, pows10 = {1};
        long long div = 1, dig = 1, pow = 1;
        while (div <= k) {
            div += dig * pow * 9;
            block_div.push_back(div);
            dig++;
            pow *= 10;
            pows10.push_back(pow);
        }
        long long curr_pow = 0;
        for (int i = 0; i < block_div.size(); i++) {
            if (block_div[i] >= k) {
                curr_pow = i - 1;
                break;
            }
        }
        long long curr_idx = pows10[curr_pow] + (k - block_div[curr_pow]) / (curr_pow + 1);
        long long curr_dig = (k - block_div[curr_pow]) % (curr_pow + 1);
        long long b = curr_idx / 10;
        long long ans = -1;
        if (b % 2 == 0) {
            ans = to_string(10 * b + (curr_idx % 10))[curr_dig] - '0';
        }
        else if (b % 2 == 1) {
            ans = to_string(10 * b + 9 - (curr_idx % 10))[curr_dig] - '0';
        }
        return ans;
    }
};