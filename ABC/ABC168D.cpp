#include <iostream>
#include <vector>

void ABC168D() {
    int n, m, a_i, b_i;
    std::cin >> n >> m;
    std::vector<std::vector<int>> adj_list(n, std::vector<int>());
    for (int i = 0; i < m; i++) {
        std::cin >> a_i >> b_i;
        adj_list[a_i - 1].push_back(b_i - 1);
        adj_list[b_i - 1].push_back(a_i - 1);
    }
    // TODO: solve
}

int main() {
    ABC168D();
    return 0;
}