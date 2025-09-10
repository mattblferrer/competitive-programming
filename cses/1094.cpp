#include <bits/stdc++.h>

long long CSES1094() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    long long moves = 0;
    for (int i = 0; i < n - 1; i++) {
        if (a[i + 1] - a[i] < 0) {
            moves += a[i] - a[i + 1];
            a[i + 1] = a[i];
        }
    }
    return moves;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1094() << "\n";
    return 0;
}