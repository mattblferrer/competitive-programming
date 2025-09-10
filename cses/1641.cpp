#include <bits/stdc++.h>

void CSES1641() {
    int n, x, a_i;
    std::cin >> n >> x;
    std::vector<std::pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        a[i] = {a_i, i + 1};
    }
    std::sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        int y = a[i].first, l = i + 1, r = n - 1;
        while (l < r) {
            if (a[l].first + a[r].first > x - y) r--;
            else if (a[l].first + a[r].first < x - y) l++;
            else {
                std::cout << a[i].second << " " << a[l].second << " " << a[r].second;
                return;
            }
        }
    }
    std::cout << "IMPOSSIBLE";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    CSES1641();
    return 0;
}