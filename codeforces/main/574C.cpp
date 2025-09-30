#include <bits/stdc++.h>

std::string problem574C() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        while (a[i] % 2 == 0) a[i] /= 2;
        while (a[i] % 3 == 0) a[i] /= 3;
    }
    for (int i = 0; i < n - 1; i++) {
        if (a[i] != a[i + 1]) return "No";
    }
    return "Yes";
}

int main() {
    std::cout << problem574C();
    return 0;
}