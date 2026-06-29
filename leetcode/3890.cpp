class Solution {
public:
    vector<int> findGoodIntegers(int n) {
        vector<int> ans;
        map<int, int> cnt;
        for (long long a = 1; a * a * a <= n; a++) {
            for (long long b = a; b * b * b <= n; b++) {
                long long a3 = a * a * a, b3 = b * b * b;
                if (a3 + b3 > n) break;
                cnt[a3 + b3]++;
            }
        }
        for (auto pair : cnt) {
            if (pair.second > 1) ans.push_back(pair.first);
        }
        return ans;
    }
};