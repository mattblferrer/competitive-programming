#include <bits/stdc++.h>

void CSES1068() {
    long long n;
    std::cin >> n;
    while (n > 1) {
        std::cout << n << " ";
        if (n % 2 == 0) n /= 2;
        else n = 3 * n + 1;
    }
    std::cout << 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    CSES1068();
    return 0;
}