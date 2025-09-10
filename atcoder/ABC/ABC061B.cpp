#include <iostream>
#include <vector>

void ABC061B() {
    int n, m, a_i, b_i;
    std::cin >> n >> m;
    std::vector<std::vector<int>> adj_mat(n + 1, std::vector<int> (n + 1, 0));
    for (int i = 0; i < m; i++) {
        std::cin >> a_i >> b_i;
        adj_mat[a_i][b_i]++;
        adj_mat[b_i][a_i]++;
    }
    for (int i = 1; i <= n; i++) {
        int neighbors = 0;
        for (int j = 1; j <= n; j++) {
            neighbors += adj_mat[i][j];
        }
        std::cout << neighbors << "\n";
    }
}

int main() {
    ABC061B();
    return 0;
}