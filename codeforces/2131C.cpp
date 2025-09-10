#include <bits/stdc++.h>

std::string problem2131C() {
    int n, k, s_i, t_i;
    std::cin >> n >> k;
    std::map<int, int> smod, tmod;
    for (int i = 0; i < n; i++) {
        std::cin >> s_i;
        smod[s_i % k]++;
        smod[k - (s_i % k)]++;
    }
    for (int i = 0; i < n; i++) {
        std::cin >> t_i;
        tmod[t_i % k]++;
        tmod[k - (t_i % k)]++;
    }
    for (const auto& pair: smod) {
        if (pair.second != tmod[pair.first]) return "NO";
    }
    return "YES";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2131C() << "\n";
    }
    return 0;
}