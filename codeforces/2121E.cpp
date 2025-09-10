#include <bits/stdc++.h>

int problem2121E() {
    std::string l, r;
    std::cin >> l >> r;
    int ans = 0, common = 0;
    for (int i = 0; i < l.size(); i++) {
        if (l[i] == r[i]) {
            ans += 2;
            common++;
        }
        else break;
    }
    if (common == l.size()) return ans;
    if (r[common] - l[common] > 1) return ans;
    for (int i = common + 1; i < l.size(); i++) {
        if (l[i] == '9' && r[i] == '0') ans++;
        else break;
    }
    return ans + 1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2121E() << "\n";
    }
    return 0;
}