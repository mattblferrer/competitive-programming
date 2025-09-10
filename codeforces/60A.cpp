#include <bits/stdc++.h>

int problem60A() {
    int n, m;
    std::cin >> n >> m;
    std::vector<bool> p(n + 1, true);
    std::string w_1, w_2, w_3, w_4;
    int w_5;

    p[0] = false;
    for (int i = 0; i < m; i++) {
        std::cin >> w_1 >> w_2 >> w_3 >> w_4 >> w_5;
        if (w_3 == "right") {
            for (int j = 1; j <= w_5; j++) {
                p[j] = false;
            }
        }
        else if (w_3 == "left") {
            for (int j = w_5; j <= n; j++) {
                p[j] = false;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n + 1; i++) {
        if (p[i]) ans++;
    }
    if (ans == 0) return -1;
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << problem60A() << "\n";
    return 0;
}