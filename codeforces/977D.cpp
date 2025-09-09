#include <bits/stdc++.h>

void problem977D() {
    long long n, a_i;
    std::cin >> n;
    std::map<long long, std::set<long long>> a;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        long long fac = 0, test = a_i;
        while (test % 3 == 0) {
            test /= 3;
            fac--;
        }
        a[fac].insert(a_i);
    }
    for (const auto& s: a) {
        for (long long a_i: s.second) { 
            std::cout << a_i << " ";
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    problem977D();
    return 0;
}