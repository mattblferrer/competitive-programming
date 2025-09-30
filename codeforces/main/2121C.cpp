#include <bits/stdc++.h>

int problem2121C() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> a(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
    std::vector<std::pair<int, int>> max_coords;
    int max_val = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] > max_val) {
                max_val = a[i][j];
                max_coords.clear();
                max_coords.push_back({i, j});
            }
            else if (a[i][j] == max_val) {
                max_coords.push_back({i, j});
            }
        }
    }
    if (max_coords.size() <= 2) return max_val - 1;
    bool chosen = false, valid = true;
    int r1 = max_coords[0].first;
    int c1 = max_coords[0].second;
    int r2, c2;

    for (int i = 0; i < max_coords.size(); i++) {
        int r = max_coords[i].first;
        int c = max_coords[i].second;
        if (r != r1 && c != c1) {
            r2 = r;
            c2 = c;
            chosen = true;
            break;
        }
    }
    if (!chosen) return max_val - 1;
    
    // test pts either (r1, c2) or (r2, c1)
    for (int i = 0; i < max_coords.size(); i++) {
        int r = max_coords[i].first;
        int c = max_coords[i].second;
        if (r != r1 && c != c2) {
            valid = false;
            break;
        }
    }
    if (valid) return max_val - 1;
    valid = true;
    for (int i = 0; i < max_coords.size(); i++) {
        int r = max_coords[i].first;
        int c = max_coords[i].second;
        if (r != r2 && c != c1) {
            valid = false;
            break;
        }
    }
    if (valid) return max_val - 1;
    return max_val;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2121C() << "\n";
    }
    return 0;
}