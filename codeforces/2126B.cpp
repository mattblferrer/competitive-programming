#include <bits/stdc++.h>

int problem2126B() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    int ans = 0, curr = 0;
    for (int i = 0; i < n; i++) {
        if (curr == k) {
            curr = 0;
            ans++;
            continue;
        }
        if (a[i] == 0) {
            curr++;
        }
        else {
            curr = 0;
        }
    }
    if (curr == k) ans++;
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2126B() << "\n";
    }
    return 0;
}