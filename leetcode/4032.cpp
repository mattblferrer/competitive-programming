class Solution {
public:
    vector<int> sieve(int n) {
        vector<int> spf(n + 1);
        for (int i = 0; i <= n; i++) spf[i] = i;
        for (int i = 2; i * i <= n; i++) {
            for (int j = i * i; j <= n; j += i) {
                spf[j] = min(spf[j], i);
            }
        }
        return spf;
    }
    map<int, int> factorize(vector<int> &spf, int n) {
        map<int, int> res;
        while (spf[n] != n) {
            res[spf[n]]++;
            n /= spf[n];
        }
        if (n != 1) res[n]++;
        return res;
    }
    int longestSubarray(vector<int> &nums, int k) {
        vector<int> spf = sieve(100'000);

        map<int, int> window;
        int n = nums.size(), ans = 0, left = 0, right = 0;
        while (right != n) {
            map<int, int> fr = factorize(spf, nums[right]);
            for (auto &[xi, yi] : fr) {
                window[xi] += yi;
            }
            right++;
            while (window.size() > k) {
                map<int, int> fl = factorize(spf, nums[left]);
                for (auto &[xi, yi] : fl) {
                    window[xi] -= yi;
                    if (window[xi] == 0) window.erase(xi);
                }
                left++;
            }
            ans = max(ans, right - left);
        }
        return ans;
    }
};