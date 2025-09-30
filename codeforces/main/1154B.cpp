#include <bits/stdc++.h>

int problem1154B() {
    int n, a_i;
    std::cin >> n;
    std::map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        cnt[a_i]++;
    }
    if (cnt.size() > 3) return -1;
    int max_a = 0, mid_a = 0, min_a = 101;
    for (const auto& pair: cnt) {
        int a_i = pair.first, c = pair.second;
        max_a = std::max(max_a, a_i);
        min_a = std::min(min_a, a_i);
    }
    if (cnt.size() == 3) {
        if ((max_a + min_a) % 2 == 1) return -1;
        if (cnt[(max_a + min_a) / 2]) return (max_a - min_a) / 2;
        return -1;
    }
    if (cnt.size() == 2) {
        if ((max_a - min_a) % 2 == 0) return (max_a - min_a) / 2;
        return max_a - min_a;
    }
    return 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << problem1154B() << "\n";
    return 0;
}