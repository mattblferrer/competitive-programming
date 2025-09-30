#include <bits/stdc++.h>

std::string problem2126C() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> h(n);
    for (int i = 0; i < n; i++) {
        std::cin >> h[i];
    }
    int s = h[k - 1];
    std::sort(h.begin(), h.end());
    for (int i = 0; i < n; i++) {
        if (h[i] == s) {
            k = i;
            break;
        }
    }
    int w = 1;
    for (int i = k; i < n - 1; i++) {
        if (h[i + 1] - h[i] > h[i] - w + 1) return "NO";
        w += (h[i + 1] - h[i]);
    }
    return "YES";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2126C() << "\n";
    }
    return 0;
}