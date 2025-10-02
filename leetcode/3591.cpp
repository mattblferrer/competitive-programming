#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool is_prime(long long n) {
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        for (long long i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return n > 1;
    }
    bool checkPrimeFrequency(vector<int>& nums) {
        map<int, int> freq;
        for (int i = 0; i < nums.size(); i++) freq[nums[i]]++;
        for (const auto& pair: freq) {
            if (is_prime(pair.second)) return true;
        }
        return false;
    }
};