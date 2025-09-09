#include <bits/stdc++.h>

void problem2037D() {
    int n, m, l, l_i, r_i, x_i, v_i, p_ctr = 0, jump = 1, ans = 0;
    std::cin >> n >> m >> l;
    std::vector<std::pair<int, int>> h(n);
    std::vector<std::vector<int>> p(n + 1);  // powerups categorized by hurdle
    std::priority_queue<int> h_pq;  // powerups sorted by value v_i
    for (int i = 0; i < n; i++) {
        std::cin >> l_i >> r_i;
        h[i] = {l_i, r_i};
    }
    for (int i = 0; i < m; i++) {
        std::cin >> x_i >> v_i;
        while (p_ctr < n && x_i > h[p_ctr].first) {
            p_ctr++;
        }
        p[p_ctr].push_back(v_i);
    }
    for (int i = 0; i < n; i++) {
        l_i = h[i].first;
        r_i = h[i].second;
        for (int j: p[i]) {
            h_pq.push(j);
        }
        while (jump < r_i - l_i + 2) {  // including bounds [l_i, r_i]
            if (h_pq.empty()) {
                std::cout << "-1\n";
                return;
            }
            jump += h_pq.top();
            h_pq.pop();
            ans++;
        }
    }
    std::cout << ans << '\n';
    return;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2037D();	
    }
    return 0;
}