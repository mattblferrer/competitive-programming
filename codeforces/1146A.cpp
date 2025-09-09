#include <bits/stdc++.h>

int problem1146A() {
    std::string s;
    std::cin >> s;
    int a_cnt = 0, n = s.size();
    for (int i = 0; i < n; i++) {
        if (s[i] == 'a') a_cnt++;
    }
    return std::min(n, a_cnt * 2 - 1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << problem1146A() << "\n";
    return 0;
}