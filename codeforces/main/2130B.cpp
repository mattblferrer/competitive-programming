#include <bits/stdc++.h>

void problem2130B() {
    int n, s;
    std::cin >> n >> s;
    std::vector<int> cnt(3), a(n + 1);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        cnt[a[i]]++;
        sum += a[i];
    }
    if (s < sum) {
        for (int i = 1; i <= n; i++) {
            std::cout << a[i] << " ";
        }
        std::cout << "\n";
        return;
    }
    if (s >= sum && s != sum + 1) {
        std::cout << "-1\n";
        return;
    }
    for (int i = 0; i < cnt[0]; i++) std::cout << "0 ";
    for (int i = 0; i < cnt[2]; i++) std::cout << "2 ";
    for (int i = 0; i < cnt[1]; i++) std::cout << "1 ";
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2130B();
    }
    return 0;
}