#include <bits/stdc++.h>

long long problemF() {
    long long INF = 2000000001;
    long long n, s, k, ans_f = 0, ans_b = 0;
    std::cin >> n >> s >> k;
    std::vector<long long> x(n + 2);
    x[0] = -INF;
    x[n + 1] = INF;
    for (int i = 1; i <= n; i++) {
        std::cin >> x[i];
    }
    for (int i = 0; i < n + 2; i++) {
        x[i] *= 2;
    }
    s *= 2;
    k *= 2;

    std::sort(x.begin(), x.end());
    std::vector<long long> plat_l(n + 2, INF), plat_r(n + 2, -INF);
    for (int i = 1; i <= n; i++) {
        long long lo = x[i - 1];
        long long hi = x[i + 1];

        if (x[i] - lo - s < 0 || hi - x[i] - s < 0) return -1;  // check if possible within bounds < s
        plat_r[i] = std::min(x[i] + k / 2, hi - s / 2);  // greedy right edge of platform
        plat_l[i] = std::max(plat_r[i - 1], x[i] - (plat_r[i] - x[i]));  // match left l/2 to right l/2 w/o overlap
        plat_r[i] = std::min(plat_r[i], x[i] + (x[i] - plat_l[i]));  // rematch right l/2 to left l/2 w/o overlap
        ans_f += (plat_r[i] - plat_l[i]) / 2;
    }
    return ans_f;
}

int main() {
    std::cout << problemF();
    return 0;
}