#include <bits/stdc++.h>

int ABC088B() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end(), std::greater());
    std::vector<int> sc = {0, 0};
    for (int i = 0; i < n; i++) {
        sc[i % 2] += a[i];
    }
    return sc[0] - sc[1];
}

int main() {
    std::cout << ABC088B();
    return 0;
}