#include <bits/stdc++.h>

long long ABC070C() {
    long long n, t_i, ans = 1;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> t_i;
        ans = std::lcm(ans, t_i);
    }
    return ans;
}

int main() {
    std::cout << ABC070C();
    return 0;
}