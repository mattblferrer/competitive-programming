#include <bits/stdc++.h>

void problem102861N() {
    long long m, n, k, m_i, n_i, d_i;
    std::cin >> m >> n >> k;
    std::vector<long long> c(n + 1), primes(m + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> c[i];
    }
    std::vector<std::vector<std::pair<long long, long long>>> m_edges(m + 1);
    for (int i = 1; i <= k; i++) {
        std::cin >> m_i >> n_i >> d_i;
        m_edges[m_i].push_back({n_i, d_i});
    }
    long long p = 2;
    for (int i = 1; i <= m; i++) {
        const auto& pair = m_edges[i][0];
        n_i = pair.first, d_i = pair.second;
        while (true) {
            if (p * p > c[n_i]) {
                primes[i] = c[n_i];
                p = c[n_i];
                break;
            }
            long long curr = p;
            for (int j = 2; j <= d_i; j++) {
                curr *= p;
            }
            if (c[n_i] % curr == 0) {
                primes[i] = p;      
                break;
            }
            p++;
        }
        for (const auto& pair_2: m_edges[i]) {
            long long curr = p;
            for (int j = 2; j <= pair_2.second; j++) {
                curr *= p;
            }
            c[pair_2.first] /= curr;
        }
    }
    for (int i = 1; i <= m; i++) {
        std::cout << primes[i] << " ";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    problem102861N();
    return 0;
}