class Solution {
public:
    int squareSum(int n) {
        int ans = 0;
        while (n > 0) {
            ans += (n % 10) * (n % 10);
            n /= 10;
        }
        return ans;
    }

    int digitSum(int n) {
        int ans = 0;
        while (n > 0) {
            ans += (n % 10);
            n /= 10;
        }
        return ans;
    }

    bool checkGoodInteger(int n) {
        return squareSum(n) - digitSum(n) >= 50;
    }
}
