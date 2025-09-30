#include <bits/stdc++.h>

void problem239A() {
    int y, k, n;
    std::cin >> y >> k >> n;
    int curr = k - y % k;
    if (y + curr > n) {
        std::cout << -1;
        return;
    }
    while (y + curr <= n) {
        std::cout << curr << " ";
        curr += k;
    }
}

int main() {
    problem239A();
    return 0;
}