#include <bits/stdc++.h>

int problem43C() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::vector<int> rem(3);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        rem[a[i] % 3]++;
    }
    return rem[0] / 2 + std::min(rem[1], rem[2]);
}

int main() {
    std::cout << problem43C();
    return 0;
}