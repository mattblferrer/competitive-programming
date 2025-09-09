#include <bits/stdc++.h>

int problem2112B() {
    int INF = 10000;
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    bool is_beautiful = false;
    for (int i = 0; i < n - 1; i++) {
        if (abs(a[i] - a[i + 1]) <= 1) {
            is_beautiful = true;
        }
    }
    if (is_beautiful) return 0;
    for (int i = 1; i < n - 1; i++) {
        if (a[i - 1] < a[i] && a[i] > a[i + 1]) return 1;
        if (a[i - 1] > a[i] && a[i] < a[i + 1]) return 1;
    }
    return -1;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2112B() << "\n";
    }
    return 0;
}