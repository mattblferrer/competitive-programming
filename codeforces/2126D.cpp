#include <bits/stdc++.h>

long long problem2126D() {
    int n, k, l_i, r_i, real_i;
    std::cin >> n >> k;
    std::vector<std::vector<int>> cas(n);
    for (int i = 0; i < n; i++) {
        std::cin >> l_i >> r_i >> real_i;
        cas[i] = {l_i, r_i, real_i};
    }
    std::sort(cas.begin(), cas.end(), [](std::vector<int> a, std::vector<int> b){
        return a[0] < b[0];
    });
    long long ans = k;
    for (int i = 0; i < n; i++) {
        l_i = cas[i][0];
        r_i = cas[i][1];
        real_i = cas[i][2];
        if (l_i <= ans && ans <= r_i && real_i > ans) ans = real_i;
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2126D() << "\n";
    }
    return 0;
}