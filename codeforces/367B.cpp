#include <bits/stdc++.h>

void problem367B() {
    int n, m, p;
    std::cin >> n >> m >> p;
    std::vector<int> a(n + 1), b(m + 1);
    std::map<int, int> b_map;
    std::set<int> index;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        std::cin >> b[i];
        b_map[b[i]]++;
    }
    for (int i = 1; i <= p; i++) {
        std::map<int, int> a_map;
        for (int j = 0; j < m; j++) {
            int curr = i + j * p;
            if (curr > n) break;
            a_map[a[curr]]++;
        }
        for (int j = m - 1; j <= n / p; j++) {
            int curr = i + j * p, prev = i + (j - m) * p, valid = 1;
            if (curr > n) break;
            if (prev > 0) {
                a_map[a[curr]]++;
                a_map[a[prev]]--;
            }
            for (const auto& pair: a_map) {
                if (a_map[pair.first] == b_map[pair.first]) continue;
                valid = 0;
                break;
            }
            if (valid) {
                index.insert(prev + p);
            }
            
        }
    }
    std::cout << index.size() << "\n";
    for (int i: index) {
        std::cout << i << " ";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    problem367B();
    return 0;
}