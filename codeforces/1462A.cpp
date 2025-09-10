#include <bits/stdc++.h>

void problem1462A() {
    int n;
    std::cin >> n;
    std::vector<int> b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    for (int i = 0; i < n / 2; i++) {
        std::cout << b[i] << " " << b[n - i - 1] << " ";
    }
    if (n % 2 == 1) std::cout << b[n / 2] << " ";
    std::cout << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem1462A();
    }
    return 0;
}