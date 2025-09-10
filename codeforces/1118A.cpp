#include <bits/stdc++.h>

long long problem1118A() {
    long long n, a, b;
    std::cin >> n >> a >> b;
    if (a * 2 < b) return n * a;
    else return (n / 2) * b + (n % 2) * a;
}

int main() {
    int q;
    std::cin >> q;
    for (int i = 0; i < q; i++) {
        std::cout << problem1118A() << '\n';
    }
    return 0;
}