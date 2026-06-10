class Solution {
public:
    int smallestNumber(int n, int t) {
        while (true) {
            int prod = 1, check = n;
            while (check > 0) {
                prod *= check % 10;
                check /= 10;
            }
            if (prod % t == 0) return n;
            n++;
        }
    }
};