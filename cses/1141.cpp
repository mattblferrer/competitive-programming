#include <bits/stdc++.h>

int CSES1141() {
    int n;
    std::cin >> n;
    std::vector<int> k(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> k[i];
    }
    std::map<int, int> seen;
    int curr = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        curr = std::max(curr, seen[k[i]]);
        ans = std::max(ans, i - curr);
        seen[k[i]] = i;
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1141() << "\n";
    return 0;
}