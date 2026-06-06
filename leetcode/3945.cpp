#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int digitFrequencyScore(int n) {
        int ans = 0;
        vector<int> freq(10);
        while (n > 0) {
            freq[n % 10]++;
            n /= 10;
        }
        for (int i = 0; i < 10; i++) ans += i * freq[i];
        return ans;
    }
};