#include <bits/stdc++.h>

void problem2122C() {
    int n, x_i, y_i;
    std::cin >> n;
    std::vector<std::vector<int>> coords(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x_i >> y_i;
        coords[i] = {x_i, y_i, i + 1};
    }
    // TODO: solve
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