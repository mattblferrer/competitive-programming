#include <bits/stdc++.h>

void ABC119D() {
    long long a, b, q, s_i, t_i, x_i, INF = pow(10, 11), min_dist;
    std::cin >> a >> b >> q;
    std::vector<long long> s, t;
    s.push_back(-INF);
    s.push_back(INF);
    t.push_back(-INF);
    t.push_back(INF);

    for (int i = 0; i < a; i++) {
        std::cin >> s_i;
        s.push_back(s_i);
    }
    for (int i = 0; i < b; i++) {
        std::cin >> t_i;
        t.push_back(t_i);
    }
    std::sort(s.begin(), s.end());
    std::sort(t.begin(), t.end());
    for (int i = 0; i < q; i++) {
        std::cin >> x_i;
        min_dist = INF;
        long long prev_s = *std::prev(std::lower_bound(s.begin(), s.end(), x_i));
        long long next_s = *std::upper_bound(s.begin(), s.end(), x_i);
        long long prev_t = *std::prev(std::lower_bound(t.begin(), t.end(), x_i));
        long long next_t = *std::upper_bound(t.begin(), t.end(), x_i);
        
        min_dist = std::min({
            std::abs(next_t - x_i) + std::abs(next_t - prev_s),  // west s, east t (s first)
            std::abs(next_s - x_i) + std::abs(next_s - prev_t),  // east s, west t (s first)
            std::abs(prev_s - x_i) + std::abs(prev_t - prev_s),  // west s, west t (s first)
            std::abs(next_s - x_i) + std::abs(next_s - next_t),  // east s, east t (s first)
            std::abs(prev_s - x_i) + std::abs(next_t - prev_s),  // west s, east t (t first)
            std::abs(prev_t - x_i) + std::abs(next_s - prev_t),  // east s, west t (t first)
            std::abs(prev_t - x_i) + std::abs(prev_t - prev_s),  // west s, west t (t first)
            std::abs(next_t - x_i) + std::abs(next_s - next_t)   // east s, east t (t first)
        });
        std::cout << min_dist << '\n';
    }
}

int main() {
    ABC119D();
    return 0;
}