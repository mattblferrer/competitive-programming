#include <bits/stdc++.h>

void problem2122C() {
    int n, x_i, y_i;
    std::cin >> n;
    std::vector<std::vector<int>> xsort(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x_i >> y_i;
        xsort[i] = {x_i, y_i, i + 1};
    }
    std::sort(xsort.begin(), xsort.end(), [](const auto& a, const auto& b) {
        return a[0] < b[0];
    });
    std::vector<std::vector<int>> low_x, high_x;
    for (int i = 0; i < n / 2; i++) {
        low_x.push_back(xsort[i]);
    }
    for (int i = n / 2; i < n; i++) {
        high_x.push_back(xsort[i]);
    }
    std::sort(low_x.begin(), low_x.end(), [](const auto& a, const auto& b) {
        return a[1] < b[1];
    });
    std::sort(high_x.begin(), high_x.end(), [](const auto& a, const auto& b) {
        return a[1] < b[1];
    });
    for (int i = 0; i < n / 2; i++) {
        std::cout << low_x[i][2] << " " << high_x[n / 2 - i - 1][2] << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2122C();
    }
    return 0;
}