#include <bits/stdc++.h>

long long CSES2428() {
    long long n, k;
    std::cin >> n >> k;
    std::vector<long long> x(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> x[i];
    }
    long long ans = 0, l = 0;
    std::map<long long, long long> seen;
    std::set<long long> curr;
    for (int r = 1; r <= n; r++) {
        curr.insert(x[r]);
        while (curr.size() > k) {
            l++;
            if (seen[x[l]] == l) {
                curr.erase(x[l]);
            }
        }
        ans += r - l;
        seen[x[r]] = r;
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES2428() << "\n";
    return 0;
}