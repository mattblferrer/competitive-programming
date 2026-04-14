class Solution {
public:
    long long nthUglyNumber(long long n) {
        set<long long> s;
        s.insert(1);
        vector<long long> nums = {1};
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            long long m = *s.begin();
            s.erase(m);
            s.insert(m*2);
            s.insert(m*3);
            s.insert(m*5);
            nums.push_back(m);
        }
        ans = nums.back();
        return ans;
    }
};