#include <bits/stdc++.h>

long long problem1343A() {
    long long n;
    std::cin >> n;
    for (int i = 2; i <= 32; i++) {
        if (n % (long long)(powl(2, i) - 1) == 0) return n / (long long)(powl(2, i) - 1);
    }
    return 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1343A() << "\n";
    }
    return 0;
}