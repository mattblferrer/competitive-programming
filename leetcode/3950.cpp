#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool consecutiveSetBits(int n) {
        if (n == 0) return false;

        string base2 = "";
        while (n > 0) {
            if (n & 1) base2 += '1';
            else base2 += '0';
            n /= 2;
        }
        int pairs = 0;
        for (int i = 0; i < base2.size() - 1; i++) {
            if (base2[i] == '1' && base2[i + 1] == '1') pairs++;
        }
        if (pairs == 1) return true;
        else return false;
    }
};