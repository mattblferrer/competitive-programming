#include <bits/stdc++.h>

void problem2120C() {
    long long n, m;
    std::cin >> n >> m;
    if (m < n || m > n * (n + 1) / 2) {  // impossible, too low or too high m
        std::cout << -1 << "\n";
        return;
    }

    // find possible d[i] for every i up to n
    std::vector<bool> used(n);
    std::vector<long long> d(n, 1);
    m -= n;
    for (int i = 0; i < n; i++) {
        if (m == 0) break;
        d[i] += std::min(n - i - 1, m);
        m -= d[i] - 1;
        used[d[i] - 1] = true;
    }

    // print tree representation
    int ctr = 0, prev = 1;
    std::cout << d[ctr] << "\n";  // root of the tree
    while (ctr < n - 1) {
        if (d[ctr] == 1) break;
        std::cout << d[ctr] << " " << d[ctr + 1] << "\n";
        ctr++;
        prev = d[ctr + 1];
    }
    ctr = 1;
    while (ctr < n) {
        if (!used[ctr]) {
            std::cout << prev << " " << ctr + 1 << "\n";
            prev = ctr + 1;
        }
        ctr++;
    }
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2120C();
    }
    return 0;
}