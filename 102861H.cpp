#include <bits/stdc++.h>

long long comb(long long n, long long k) {
    if (k < 0) return 0;
    if (k == 0) return 1;
    return (n * comb(n - 1, k - 1)) / k;
}

long long backtrack(long long x, long long k, long long max_w, std::vector<long long>& w) {
    long long n = w.size();
    if (x == n) return (k == 0);
    if (w[x] > max_w) return backtrack(x + 1, k, max_w, w);
    return backtrack(x + 1, k - 1, max_w - w[x], w) + comb(n - x - 1, k);
}

long long problem102861H() {
    long long n, k, a, b, ans;
    std::cin >> n >> k;
    std::vector<long long> w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::cin >> a >> b;
    std::sort(w.begin(), w.end(), std::greater<long long>());
    ans = backtrack(0, k, b, w) - backtrack(0, k, a - 1, w);
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << problem102861H();
    return 0;
}