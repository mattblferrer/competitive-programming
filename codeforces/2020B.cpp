#include <bits/stdc++.h>

long long problem2020B() {
    long long k, ans;
    std::cin >> k;
    
    long long left = -1, right = (long long)(2 * pow(10, 18));
    while (right - left > 1) {
        long long mid = (left + right) / 2;
        if (mid - (long long)sqrtl(mid) >= k) {
            right = mid;
        }
        else {
            left = mid;
        }
    }
    return right;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2020B() << "\n";
    }
    return 0;
}