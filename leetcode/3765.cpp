#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPrime(int num) {
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        }
        return (num > 1);
    }

    bool completePrime(int num) {
        string nstr = to_string(num);
        for (int i = 1; i <= nstr.size(); i++) {
            string pref = nstr.substr(0, i);
            if (!isPrime(stoi(pref))) return false;
        }
        for (int i = 1; i <= nstr.size(); i++) {
            string suff = nstr.substr(nstr.size() - i, i);
            if (!isPrime(stoi(suff))) return false;
        }
        return true;
    }
};