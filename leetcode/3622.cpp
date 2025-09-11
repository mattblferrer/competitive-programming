#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool checkDivisibility(int n) {
        int original = n;
        int sum = 0;
        int product = 1;
        while (n > 0) {
            sum += n % 10;
            product *= n % 10;
            n /= 10;
        }
        return (original % (sum + product)) == 0;
    }
};