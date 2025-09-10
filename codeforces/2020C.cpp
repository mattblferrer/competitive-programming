#include <bits/stdc++.h>

long long problem2020C() {
    long long a = 0, b, c, d;
    std::cin >> b >> c >> d;
    for (long long i = 0; i < 64; i++) {
        long long p = 1LL << i;
        if ((b & p) == 0 && (c & p) != 0 && (d & p) != 0) return -1;  // 011
        if ((b & p) != 0 && (c & p) == 0 && (d & p) == 0) return -1;  // 100
        if ((b & p) == 0 && (c & p) == 0 && (d & p) != 0) a |= p;  // 001
        if ((b & p) != 0 && (c & p) != 0 && (d & p) == 0) a |= p;  // 110
    }
    return a;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2020C() << "\n";
    }
    return 0;
}