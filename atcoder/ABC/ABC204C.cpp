#include <iostream>
#include <vector>
#include <queue>

int ABC204C() {
    int n, m, a_i, b_i;
    std::cin >> n >> m;
    std::vector<std::vector<int>> adj_list(n, std::vector<int>());
    for (int i = 0; i < m; i++) {
        std::cin >> a_i >> b_i;
        adj_list[a_i - 1].push_back(b_i - 1);
    }

    std::queue<int> q;
    int pairs = 0;
    for (int start = 0; start < n; start++) {
        std::vector<bool> seen(n);
        q.push(start);
        seen[start] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            pairs++;

            for (int v: adj_list[u]) {
                if (seen[v]) continue;
                seen[v] = true;
                q.push(v);
            }
        }
    }
    return pairs;
}   

int main() { 
    std::cout << ABC204C();
    return 0;
}