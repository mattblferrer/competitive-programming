#include <bits/stdc++.h>

int problem2130A() {
    int n, s_i;
    std::cin >> n;
    std::map<int, int> s;
    for (int i = 0; i < n; i++) {
        std::cin >> s_i;
        s[s_i]++;
    }
    int ans = 0;
    while (s[0]) {
        ans++;
        s[0]--;
    }
    for (auto pair: s) {
        ans += pair.first * pair.second;
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2130A() << "\n";
    }
    return 0;
}