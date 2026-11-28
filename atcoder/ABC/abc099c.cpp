#include <iostream>

int ABC099C() {
    int n;
    std::cin >> n;
    int* dp = new int[n + 1];
    for (int i = 1; i < n + 1; i++) {
        dp[i] = n;
    }
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j *= 6) {
            dp[i] = std::min(dp[i], dp[i - j] + 1);
        }
        for (int j = 1; j <= i; j *= 9) {
            dp[i] = std::min(dp[i], dp[i - j] + 1);
        }
    }
    return dp[n];
}

int main() { 
    std::cout << ABC099C();
    return 0;
}