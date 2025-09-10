#include <bits/stdc++.h>

long long CSES3420() {
    long long n;
    std::cin >> n;
    std::vector<long long> x(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> x[i];
    }
    long long ans = 0, l = 0;
    std::set<long long> curr;
    for (int r = 1; r <= n; r++) {
        if (curr.count(x[r]) == 0) {
            curr.insert(x[r]);
        }
        else {
            l++;
            while (x[l] != x[r]) {
                curr.erase(x[l]);
                l++;
            }
        }
        ans += r - l;
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES3420() << "\n";
    return 0;
}