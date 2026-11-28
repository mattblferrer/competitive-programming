#include <iostream>
#include <vector>

int ABC166C() {
    int n, m, a_i, b_i;
    std::cin >> n >> m;
    std::vector<int> h(n);
    for (int i = 0; i < n; i++) {
        std::cin >> h[i];
    }
    std::vector<std::vector<int>> adj_list(n, std::vector<int>());
    for (int i = 0; i < m; i++) {
        std::cin >> a_i >> b_i;
        adj_list[a_i - 1].push_back(b_i - 1);
        adj_list[b_i - 1].push_back(a_i - 1);
    }
    int good = 0;
    for (int i = 0; i < n; i++) {
        bool is_good = true;
        for (int j: adj_list[i]) {
            if (h[i] <= h[j]) {
                is_good = false;
                break;
            }
        }
        if (is_good) good++;
    }
    return good;
}

int main() {
    std::cout << ABC166C();
    return 0;
}