#include <bits/stdc++.h>

void problem2122C() {
    int n, x_i, y_i;
    std::cin >> n;
    std::vector<std::pair<int, int>> xsort(n), ysort(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x_i >> y_i;
        xsort[i] = {x_i, y_i};
        ysort[i] = {x_i, y_i};
    }
    std::sort(xsort.begin(), xsort.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });
    std::sort(ysort.begin(), ysort.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });
    // TODO: upsolve
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