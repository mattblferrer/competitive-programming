#include <bits/stdc++.h>

void problem2130C() {
    int n, a_i, b_i;
    std::cin >> n;
    std::vector<int> line(2 * n + 1);
    std::vector<int> index;
    for (int i = 1; i <= n; i++) {
        std::cin >> a_i >> b_i;
        bool all = true;
        for (int j = a_i; j < b_i; j++) {
            if (!line[j]) {
                all = false;
            }
            line[j] = 1;
        }
        if (all) continue;
        index.push_back(i);
    }
    std::cout << index.size() << "\n";
    for (int i = 0; i < index.size(); i++) {
        std::cout << index[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2130C();
    }
    return 0;
}