#include <bits/stdc++.h>

long long CSES1083() {
    long long n, a_i, sum = 0;
    std::cin >> n;
    for (int i = 0; i < n - 1; i++) {
        std::cin >> a_i;
        sum += a_i;
    }
    return n * (n + 1) / 2 - sum;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1083() << "\n";
    return 0;
}